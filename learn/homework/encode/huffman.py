#哈夫曼编码的编解码实现

from collections import defaultdict
import heapq

class Huffman:
    #初始化
    def __init__(self):
        self.tree = [] #哈夫曼树
        self.code = {} #字母对应的哈夫曼编码
    
    def reset(self):
        self.tree = []
        self.code = {}
    
    #哈夫曼编码
    def encode(self, text):
        #清空哈夫曼树和哈夫曼编码
        self.reset()
        
        #统计字符频率
        freq = defaultdict(int)
        for c in text:
            freq[c] += 1
        
        #构建哈夫曼树，左右孩子用下标表示
        self.tree = [{'freq': f, 'char': c, 'left': -1, 'right': -1, 'index': i} for i, (c, f) in enumerate(freq.items())]
        self.root = len(self.tree)
        heap = [(node['freq'], node['index']) for node in self.tree]  # 修改这里，只存储频率和索引
        heapq.heapify(heap)
        while len(heap) > 1:
            left_index = heapq.heappop(heap)[1]
            right_index = heapq.heappop(heap)[1]
            left = self.tree[left_index]
            right = self.tree[right_index]
            left['father'] = self.root
            right['father'] = self.root
            self.root += 1
            self.tree.append({'freq': left['freq'] + right['freq'], 'left': left['index'], 'right': right['index'], 'index': len(self.tree)})
            heapq.heappush(heap, (self.tree[-1]['freq'], self.tree[-1]['index']))  # 修改这里，只存储频率和索引
        
        #生成哈夫曼编码
        for node in self.tree:
            if not 'char' in node:
                break
            
            code = ""
            char = node['char']
            while 'father' in node:
                father = self.tree[node['father']]
                if father['left'] == node['index']:
                    code = '0' + code
                else:
                    code = '1' + code
                node = father
            self.code[char] = code
            
        #对text进行编码
        encoded = ''
        for c in text:
            encoded += self.code[c]
        return encoded
    
    #哈夫曼解码
    def decode(self, encoded_text):
        #对text进行解码
        decoded = ''
        #如果树空，raise
        if not self.tree:
            raise ValueError("未编码")
        
        node = self.tree[-1]
        for c in encoded_text:
            #错误信息
            if c not in ['0', '1']:
                raise ValueError("非法字符")
            
            if c == '0':
                node = self.tree[node['left']]
            else:
                node = self.tree[node['right']]
            if 'char' in node:
                decoded += node['char']
                node = self.tree[-1]
        return decoded