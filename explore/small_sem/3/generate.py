import torch
from torch import nn
import numpy as np
from poem_train import PoetryModel

class Config(object):
    max_gen_len = 50  # 生成诗歌最长长度
    prefix_words = '白日依山尽，黄河入海流。'  # 不是诗歌的组成部分，用来控制生成诗歌的意境
    start_words = '深度学习'  # 诗歌开始
opt = Config

def generate_withpre(model, style_words, prefix_words, sentences, word2id, id2word, device):
    results = []
    input = torch.Tensor([word2id['[START]']]).view(1, 1).long()
    input = input.to(device)
    hidden = None

    pre_word = '[START]'
    index = 0

    if style_words:
        for word in style_words:
            output, hidden = model(input, hidden)
            input = (input.data.new([word2id[word]])).view(1, 1)
            
    for word in prefix_words:
        output, hidden = model(input, hidden)
        input = (input.data.new([word2id[word]])).view(1, 1)
        results.append(word)

    while(True):
        output, hidden = model(input, hidden)
        top_index = output.data[0].topk(1)[1][0].item()
        w = id2word[top_index]

        if (pre_word in {'，', '。', '！', '[START]'}):
            if index == sentences:
                break
            index += 1
        else:
            input = (input.data.new([top_index])).view(1, 1)

        results.append(w)
        pre_word = w
    return results

def gen_acrostic(model, start_words, ix2word, word2ix, device, prefix_words=None):
    """
    生成藏头诗
    start_words : u'深度学习'
    生成：
    深山通海月，度水入江流。学道无人识，习家无事心。
    """
    results = []
    start_word_len = len(start_words)
    input = torch.Tensor([word2ix['[START]']]).view(1, 1).long()
    input = input.to(device)
    hidden = None

    index = 0  # 用来指示已经生成了多少句藏头诗
    # 上一个词
    pre_word = '[START]'

    if prefix_words:
        for word in prefix_words:
            output, hidden = model(input, hidden)
            input = (input.data.new([word2ix[word]])).view(1, 1)

    for i in range(opt.max_gen_len):
        output, hidden = model(input, hidden)
        top_index = output.data[0].topk(1)[1][0].item()
        w = ix2word[top_index]

        if (pre_word in {'，', '。', '！', '[START]'}):
            # 如果遇到句号，藏头的词送进去生成

            if index == start_word_len:
                # 如果生成的诗歌已经包含全部藏头的词，则结束
                break
            else:
                # 把藏头的词作为输入送入模型
                w = start_words[index]
                index += 1
                input = (input.data.new([word2ix[w]])).view(1, 1)
        else:
            # 否则的话，把上一次预测是词作为下一个词输入
            input = (input.data.new([word2ix[w]])).view(1, 1)
        results.append(w)
        pre_word = w
    return results

def getData(pklfile):
    data = np.load(pklfile, allow_pickle=True)
    data, word2id, id2word = data['data'], data['word2id'].item(), data['id2word'].item()
    return data, word2id, id2word

def processWord(words, defword):
    if words.isprintable():
        new_words = words if words else defword
    else:
        new_words = words.encode('ascii', 'surrogateescape')\
            .decode('utf8') if words else defword
    return new_words.replace(',', u'，') \
        .replace('.', u'。') \
        .replace('?', u'？')

data, word2id, id2word = getData('poem_data.npz')
style_words = '白日依山尽，黄河入海流。'#控制风格
model_type = input('请输入模型类型：') # L stands for LSTM, G stands for GRU
prefix_words = input('请输入藏头：')
style_words = processWord(style_words, '白日依山尽，黄河入海流。')
prefix_words = processWord(prefix_words, '逆天')
version = input('请输入模型版本号：')
#sentences = int(input('请输入诗歌句数：'))

device = torch.device('cuda')
if model_type == 'L':
    model = PoetryModel(len(word2id), 128, 256, model_type).to(device)
    model.load_state_dict(torch.load(f'poetry_gen_{version}_LSTM.pth'))
elif model_type == 'G':
    model = PoetryModel(len(word2id), 128, 256, model_type).to(device)
    model.load_state_dict(torch.load(f'poetry_gen_{version}_GRU.pth'))

#results = generate_withpre(model, style_words, prefix_words, sentences, word2id, id2word, device)
results = gen_acrostic(model, prefix_words, id2word, word2id, device, style_words)
print(''.join(results))