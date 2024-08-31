import os
import json
import numpy as np
from gb2312_80 import gb2312_80

def _load_poems(path, prefix):
    data = []
    for filename in os.listdir(path):
        if filename.startswith(prefix):
            data.extend(_load_poem(os.path.join(path, filename)))
            
    return data

def _load_poem(file):
    content = []
    data = json.loads(open(file, 'r', encoding='utf-8').read())
    for poetry in data:
        pdata = poetry.get("paragraphs")
        if pdata != "":
            content.append(pdata)
    return content

def _padding(sequences, maxlen, value):
    num_samples = len(sequences)
    x = (np.ones((num_samples, maxlen)) * value).astype('int32')
    for id, s in enumerate(sequences):
        trunc = np.asarray(s[:maxlen]).astype('int32')
        x[id, -len(trunc):] = trunc
    return x

def load_data(path, maxlen):
    data = _load_poems(path=path, prefix='poet.tang')
    words = {_word for _sentence in data for _word in _sentence}
    
    word2id = {_word: _id for _id, _word in enumerate(words)}
    
    for s in gb2312_80:
        if s not in word2id.keys():
            word2id[s] = len(word2id)
    
    word2id['[START]'] = len(word2id)
    word2id['[END]'] = len(word2id)
    word2id['[PAD]'] = len(word2id)
    
    id2word = {_id: _word for _word, _id in word2id.items()}

    data = [['[START]'] + list(d) + ['[END]'] for d in data]
    data = [[word2id[_word] for _word in _sentence]for _sentence in data]
    data = _padding(data, maxlen, word2id['[PAD]'])
    
    np.savez_compressed('poem_data.npz', data=data, word2id=word2id, id2word=id2word)
    
load_data('chinese-poetry/simplified', 125)