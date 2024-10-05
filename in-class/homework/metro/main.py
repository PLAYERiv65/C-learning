from metro import Metro
from gui import MapViewer
import os
import sys

def resource_path(relative_path):
    """获取资源文件的绝对路径"""
    if hasattr(sys, '_MEIPASS'):
        # PyInstaller打包后的临时文件夹路径
        base_path = sys._MEIPASS
    else:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)

MAP_PATH = resource_path('beijing.json')
DATA_PATH = resource_path('metro.json')
FILE_PATH = resource_path('data.json')
COORDINATE_PATH = resource_path('coordinate.csv')

if __name__ == '__main__':
    beijing_metro = Metro(DATA_PATH, FILE_PATH, COORDINATE_PATH)
    viewer = MapViewer(MAP_PATH, beijing_metro)
    viewer.show()