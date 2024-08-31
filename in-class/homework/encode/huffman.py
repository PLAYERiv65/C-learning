from collections import defaultdict
import heapq
import matplotlib.pyplot as plt
import pandas as pd

class NODE:
    def __init__(self, freq, char):
        self.freq = freq
        self.char = char
        self.left = None
        self.right = None
        self.depth = None
        self.rank = None
        
    def __lt__(self, other):
        return self.freq < other.freq

std_freq_data = {
    'A': 0.0819, 'B': 0.0147, 'C': 0.0383, 'D': 0.0391, 'E': 0.1225,
    'F': 0.0226, 'G': 0.0171, 'H': 0.0457, 'I': 0.0710, 'J': 0.0041,
    'K': 0.0014, 'L': 0.0377, 'M': 0.0334, 'N': 0.0706, 'O': 0.0726,
    'P': 0.0289, 'Q': 0.0009, 'R': 0.0685, 'S': 0.0636, 'T': 0.0941,
    'U': 0.0258, 'V': 0.0109, 'W': 0.0159, 'X': 0.0021, 'Y': 0.0158,
    'Z': 0.0008
}

class Huffman:
    #初始化
    def __init__(self):
        self.reset()
        
    def reset(self):
        self.tree = [] #哈夫曼树
        self.code = {} #字母对应的哈夫曼编码
        self.build_tree()
        self._build_code(self.root, '')
        self.is_default = True
    
    def build_tree(self, text=None):#构建哈夫曼树
        freq_data = defaultdict(int)
        if text:
            for c in text:
                freq_data[c] += 1
            for c in freq_data:
                freq_data[c] /= len(text)
            self.is_default = False
        else:
            freq_data = defaultdict(int, std_freq_data)
            
        self.tree = [NODE(f, c) for c, f in freq_data.items()]
        heapq.heapify(self.tree)#使用堆选取最小值
        while len(self.tree) > 1:
            left = heapq.heappop(self.tree)
            right = heapq.heappop(self.tree)
            new_node = NODE(left.freq + right.freq, None)
            new_node.left = left
            new_node.right = right
            heapq.heappush(self.tree, new_node)
        
        if self.tree:
            self.root = self.tree[0]
            self.code = {}
            self._build_code(self.root, '')
            
        #绘制哈夫曼树
        self.plot_tree()
        self.show_code(freq_data)
    
    def show_code(self, freq_data):
        data = {
            "Character": [],
            "Frequency": [],
            "Code": [],
            "Code Length": []
        }
        
        #按字典序输出编码数据
        for c in sorted(self.code.keys()):
            data["Character"].append(c)
            data["Frequency"].append(f'{freq_data[c]:.4f}')
            data["Code"].append(self.code[c])
            data["Code Length"].append(len(self.code[c]))
    
        df = pd.DataFrame(data)
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.axis('tight')
        ax.axis('off')
        table = ax.table(cellText=df.values, colLabels=df.columns, cellLoc='center', loc='center')
    
        table.auto_set_font_size(False)
        table.set_fontsize(12)
        table.scale(1.2, 1.2)
    
        plt.show()

    def plot_tree(self):
        if not self.tree:
            return
        plt.figure(figsize=(15, 10))  # 设置绘图区域大小
        plt.axis('off')
        self.max_layer = 0
        self.max_x = [0] * 30
        self._dfs(self.root, 1, 1) # 通过一次dfs确定点的位置
        
        xlim = plt.gca().get_xlim()
        ylim = plt.gca().get_ylim()
        self.x_size = xlim[1] - xlim[0]  # 计算 x 轴范围的大小
        self.y_size = ylim[1] - ylim[0]  # 计算 y 轴范围的大小
        
        x, y = self._get_coordinate(self.root.rank, self.root.depth)
        self._plot_node(self.root, x, y, 1)
        plt.draw()  # 绘制图形但不阻塞
        plt.pause(0.001)
    
    def _dfs(self, node: NODE, layer, rank):
        #确定节点的位置
        node.depth = layer
        node.rank = rank
        self.max_layer = max(self.max_layer, layer)
        if node.char:
            return
        self._dfs(node.left, layer + 1, rank * 2 - 1)
        self._dfs(node.right, layer + 1, rank * 2)
    
    def _get_coordinate(self, rank, layer):
        x = rank * self.x_size/(2 ** (layer-1) + 1)
        y = (self.max_layer - layer) * self.y_size/(self.max_layer + 1)
        min_dis = 0.07 if layer<=6 else 0.1
        if x-min_dis < self.max_x[layer]:#深层节点编码更长，需要更多空间
            x = self.max_x[layer] + min_dis
        self.max_x[layer] = x
        return x, y
    
    def _plot_node(self, node: NODE, x, y, layer):
        # 绘制节点并连边
        plt.text(x, y, f'{node.char}:{node.freq:.2f}\n{self.code[node.char]}' if node.char else f'{node.freq:.2f}', ha='center', va='center', bbox=dict(facecolor='white', edgecolor='black'))
        if node.char:
            return
        
        #分别绘制左右子树
        new_x, new_y = self._get_coordinate(node.left.rank, node.left.depth)
        self._plot_edge(x, y, new_x, new_y, '0')
        self._plot_node(node.left, new_x, new_y, layer + 1)
        
        new_x, new_y = self._get_coordinate(node.right.rank, node.right.depth)
        self._plot_edge(x, y, new_x, new_y, '1')
        self._plot_node(node.right, new_x, new_y, layer + 1)
            
    def _plot_edge(self, x1, y1, x2, y2, label):
        plt.plot([x1, x2], [y1, y2], 'k-')
        plt.text((x1 + x2) / 2 + (int(label)-0.5)/40, (y1 + y2) / 2 + (y1-y2)*0.1, label, ha='center', va='center', fontsize=12, color='black')
            
    def _build_code(self, node:NODE, code):#生成哈夫曼编码
        if node.char:
            self.code[node.char] = code
        else:
            self._build_code(node.left, code + '0')
            self._build_code(node.right, code + '1')
    
    #哈夫曼编码
    def encode(self, text):
        encoded = ''
        for c in text:
            #错误信息
            if c not in self.code:
                raise ValueError("非法字符")
            encoded += self.code[c]
        return encoded
    
    #哈夫曼解码
    def decode(self, encoded_text):
        decoded = ''
        node = self.root
        for c in encoded_text:
            #错误信息
            if c not in ['0', '1']:
                raise ValueError("非法字符")
            
            if c == '0':
                node = node.left
            else:
                node = node.right
            if node.char:
                decoded += node.char
                node = self.root
        return decoded
    