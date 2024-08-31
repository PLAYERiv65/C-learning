import tkinter as tk
from gui import Application

if __name__ == "__main__":
    root = tk.Tk()
    root.title("编解码工具")
    root.geometry("300x200")  # 设置窗口大小
    root.attributes("-topmost", True)
    root.attributes("-topmost", False)
    app = Application(master=root)
    app.mainloop()