#主程序
import tkinter as tk
from gui import Application

def main():
    root = tk.Tk()
    root.title("编解码工具")
    root.geometry("300x200")  # 设置窗口大小为500x500
    app = Application(master=root)
    app.mainloop()

if __name__ == "__main__":
    main()