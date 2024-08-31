import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from huffman import Huffman
import os

#创建GUI
class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()
        self.in_content = ""
        self.out_content = ""
        self.is_default = 1
        self.huffman = Huffman()

    def create_widgets(self):
        #创建标签
        self.label = tk.Label(self, text="请选择文件")
        self.label.grid(row=0, column=0, columnspan=2, padx=5, pady=10)  # 增加垂直间距
    
        #创建按钮
        self.open_button = tk.Button(self, text="打开文件", command=self.open_file)
        self.open_button.grid(row=1, column=0, padx=10, pady=10)
    
        self.save_button = tk.Button(self, text="保存文件", command=self.save_file)
        self.save_button.grid(row=2, column=0, padx=10, pady=10)
    
        self.quit_button = tk.Button(self, text="退出", command=self.master.destroy)
        self.quit_button.grid(row=3, column=0, padx=10, pady=10)
        
        self.build_button = tk.Button(self, text="建树", command=self.build)
        self.build_button.grid(row=1, column=1, padx=10, pady=10)
        
        self.encode_button = tk.Button(self, text="编码", command=self.encode)
        self.encode_button.grid(row=2, column=1, padx=10, pady=10)
    
        self.decode_button = tk.Button(self, text="解码", command=self.decode)
        self.decode_button.grid(row=3, column=1, padx=0, pady=10) 

    def open_file(self):
        self.file_path = filedialog.askopenfilename()
        
        #检查是否为txt格式
        if not self.file_path.endswith('.txt'):
            messagebox.showerror("错误", "请选择txt文件")
            self.file_path = ""
            self.in_content = ""
            return
        self.label.config(text="已选择文件：" + os.path.basename(self.file_path))
        
        #读取
        with open(self.file_path, 'r') as f:
            self.in_content = f.read()
        self.is_default = 0

    def save_file(self):
        if not self.check(0,1):
            return
        
        #保存文件,默认txt
        if self.huffman.is_default:
            initialfile = "default.txt"
        else:
            initialfile = "custom.txt"
        file_path = filedialog.asksaveasfilename(defaultextension=".txt", initialfile = initialfile)
        with open(file_path, 'w') as f:
            f.write(self.out_content)
        messagebox.showinfo("保存", "保存成功")
        
    def build(self):
        try:
            if self.is_default:
                self.huffman.build_tree()
            else :
                self.huffman.build_tree(self.in_content)
            self.is_default = not self.is_default
                    
        except ValueError as e:
            messagebox.showerror("错误", str(e))
            return
        messagebox.showinfo("建树", "建树成功")
    
    def encode(self):
        if not self.check(1,0):
            return
        
        try:
            self.out_content = self.huffman.encode(self.in_content)
        except ValueError as e:
            messagebox.showerror("错误", str(e))
            return
        #计算压缩率
        original_size = len(self.in_content) * 8
        encoded_size = len(self.out_content)
        messagebox.showinfo("编码", "编码成功\n压缩率：{:.2f}%".format(encoded_size / original_size * 100))

    def decode(self):
        if not self.check(1,0):
            return
        
        try:
            self.out_content = self.huffman.decode(self.in_content)
        except ValueError as e:
            messagebox.showerror("错误", str(e))
            return
            
    def check(self, check_in, check_out):
        if not self.in_content and check_in:
            messagebox.showerror("错误", "请选择文件")
            return False
        
        if not self.out_content and check_out:
            messagebox.showerror("错误", "请先编解码")
            return False
        
        return True