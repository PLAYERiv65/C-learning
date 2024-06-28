#摩尔斯密码的编解码实现

class Morse:
    def __init__(self):
        self.morse_code = {
            'A': '.-', 'B': '-...', 'C': '-.-.', 'D': '-..', 'E': '.',
            'F': '..-.', 'G': '--.', 'H': '....', 'I': '..', 'J': '.---',
            'K': '-.-', 'L': '.-..', 'M': '--', 'N': '-.', 'O': '---',
            'P': '.--.', 'Q': '--.-', 'R': '.-.', 'S': '...', 'T': '-',
            'U': '..-', 'V': '...-', 'W': '.--', 'X': '-..-', 'Y': '-.--',
            'Z': '--..', '0': '-----', '1': '.----', '2': '..---', '3': '...--',
            '4': '....-', '5': '.....', '6': '-....', '7': '--...', '8': '---..',
            '9': '----.', ' ': '/'
        }
        #利用morse_code生成解码二叉树
        self.reverse_morse_code = {}
        for k, v in self.morse_code.items():
            node = self.reverse_morse_code
            for c in v:
                if c not in node:
                    node[c] = {}
                node = node[c]
            node[''] = k

    def encode(self, text):
        if not all(c.upper() in self.morse_code for c in text):
            raise ValueError("非法字符")
        return ' '.join(self.morse_code.get(c.upper(), '') for c in text)
    
    #用二叉树解码
    def decode(self, code):
        if not all(c in '.- ' for c in code):
            raise ValueError("非法字符")
        
        text = []
        node = self.reverse_morse_code
        for c in code + ' ':
            if c == ' ':
                if '' in node:
                    text.append(node[''])
                    node = self.reverse_morse_code
                else:
                    raise ValueError("非法摩尔斯密码")
            else:
                if c not in node:
                    raise ValueError("非法摩尔斯密码")
                node = node[c]
        return ''.join(text)
    