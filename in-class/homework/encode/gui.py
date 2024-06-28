#创建用户界面，实现哈夫曼、摩尔斯编解码的编解码和解码功能，进行文件输入输出
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from morse import Morse
from huffman import Huffman

#创建GUI
class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()
        self.morse = Morse()
        self.huffman = Huffman()
        self.mode = 0 #0表示未选择编解码方式，1表示哈夫曼编解码，2表示摩尔斯编解码

    def create_widgets(self):
        #创建标签
        self.label = tk.Label(self, text="请选择文件")
        self.label.grid(row=0, column=0, columnspan=2, pady=10)  # 增加垂直间距
    
        #创建按钮
        self.open_button = tk.Button(self, text="打开文件", command=self.open_file)
        self.open_button.grid(row=1, column=0, padx=10, pady=10)
    
        self.save_button = tk.Button(self, text="保存文件", command=self.save_file)
        self.save_button.grid(row=2, column=0, padx=10, pady=10)
    
        self.quit_button = tk.Button(self, text="退出", command=self.master.destroy)
        self.quit_button.grid(row=3, column=0, padx=10, pady=10)
        #按按钮切换编解码方式
        self.mode_button = tk.Button(self, text="切换编解码方式(当前：未选择)", command=self.switch_mode, bg="gray")
        self.mode_button.grid(row=1, column=1, padx=10, pady=10)
    
        self.encode_button = tk.Button(self, text="编码", command=self.encode)
        self.encode_button.grid(row=2, column=1, padx=10, pady=10)
    
        self.decode_button = tk.Button(self, text="解码", command=self.decode)
        self.decode_button.grid(row=3, column=1, padx=10, pady=10)
    
    def switch_mode(self):
        #切换编解码方式
        self.mode = (self.mode + 1) % 3
        
        #更改按钮文字和颜色
        if self.mode == 0:
            self.mode_button.config(text="切换编解码方式(当前：未选择)", bg="gray")
        elif self.mode == 1:
            self.mode_button.config(text="切换编解码方式(当前：哈夫曼)", bg="yellow")
        elif self.mode == 2:
            self.mode_button.config(text="切换编解码方式(当前：摩尔斯)", bg="green")

    def open_file(self):
        self.file_path = filedialog.askopenfilename()
        
        #检查是否为txt格式
        if not self.file_path.endswith('.txt'):
            messagebox.showerror("错误", "请选择txt文件")
            self.file_path = ""
            self.in_content = ""
            return
        self.label.config(text="已选择文件：" + self.file_path)
        
        #读取
        with open(self.file_path, 'r') as f:
            self.in_content = f.read()

    def save_file(self):
        if not hasattr(self, 'out_content'):
            messagebox.showerror("错误", "请先编码或解码")
            return
        
        #保存文件,默认txt
        if self.mode == 1:
            initialfile = "huffman.txt"
        elif self.mode == 2:
            initialfile = "morse.txt"
        else:
            initialfile = "default.txt"
        file_path = filedialog.asksaveasfilename(defaultextension=".txt", initialfile = initialfile)
        with open(file_path, 'w') as f:
            f.write(self.out_content)
        messagebox.showinfo("保存", "保存成功")
        

    def encode(self):
        if not self.mode:
            messagebox.showerror("错误", "请选择编解码方式")
            return
        
        #如果没有in_content，提示用户选择文件
        if not hasattr(self, 'in_content'):
            messagebox.showerror("错误", "请选择文件")
            return
        
        #根据mode编码
        if self.mode == 1:
            try:
                self.out_content = self.huffman.encode(self.in_content)
            except ValueError as e:
                messagebox.showerror("错误", str(e))
                return
            #计算压缩率
            original_size = len(self.in_content) * 8
            encoded_size = len(self.out_content)
            messagebox.showinfo("编码", "编码成功\n压缩率：{:.2f}%".format(encoded_size / original_size * 100))
        elif self.mode == 2:
            try:
                self.out_content = self.morse.encode(self.in_content)
            except ValueError as e:
                messagebox.showerror("错误", str(e))
                return
            messagebox.showinfo("编码", "编码成功")

    def decode(self):
        if not self.mode:
            messagebox.showerror("错误", "请选择编解码方式")
            return
        
        if not hasattr(self, 'in_content'):
            messagebox.showerror("错误", "请选择文件")
            return
        
        #根据mode解码
        if self.mode == 1:
            try:
                self.out_content = self.huffman.decode(self.in_content)
            except ValueError as e:
                messagebox.showerror("错误", str(e))
                return
        elif self.mode == 2:
            try:
                self.out_content = self.morse.decode(self.in_content)
            except ValueError as e:
                messagebox.showerror("错误", str(e))
                return
        
        messagebox.showinfo("解码", "解码成功")
