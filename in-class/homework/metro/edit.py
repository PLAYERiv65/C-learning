import json
import sys
import os
import csv
from pre_process import pre_process

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

def load_data():
    with open(DATA_PATH, 'r', encoding='utf-8') as file:
        return json.load(file)

def save_data(data):
    with open(DATA_PATH, 'w', encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4)

def load_coordinate_data():
    coordinate_data = {}
    with open(COORDINATE_PATH, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        for row in reader:
            city, code, name, district, coordinates = row['城市'], row['编号'], row['名称'], row['地区'], row['经纬度']
            coordinate_data[name] = coordinates
    return coordinate_data

def save_coordinate_data(new_coordinates):
    existing_coordinates = load_coordinate_data()
    with open(COORDINATE_PATH, 'a', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        for name, coordinates in new_coordinates.items():
            if name not in existing_coordinates:
                writer.writerow(["北京市", "未知", name, "未知", coordinates])

def add_line(data, coordinate_data):
    name = input("请输入线路名称：")
    color = input("请输入线路十六进制标识色：")
    top_speed = float(input("请输入线路最高时速："))
    average_speed = float(input("请输入线路平均时速："))
    
    stations = []
    distances = []
    
    while True:
        station = input("请输入站点名称（输入'q'结束）：")
        if station == 'q':
            break
        coordinates = input(f"请输入 {station} 的经纬度（格式：经度,纬度）：")
        stations.append(station)
        coordinate_data[f"{station}(地铁站)"] = coordinates
        
        if len(stations) > 1:
            distance = int(input(f"请输入 {stations[-2]} 和 {stations[-1]} 之间的距离："))
            distances.append(distance)
    
    new_line = {
        "Name": name,
        "Stations": stations,
        "Distances": distances,
        "Top_Speed": top_speed,
        "Average_Speed": average_speed,
        "Color": color
    }
    
    data["Lines"].append(new_line)
    save_data(data)
    save_coordinate_data(coordinate_data)
    print("添加成功！")

def delete_line(data):
    line_name = input("请输入线路名称：")
    line_found = False
    
    for line in data["Lines"]:
        if line["Name"] == line_name:
            data["Lines"].remove(line)
            line_found = True
            break
    
    if line_found:
        save_data(data)
        print("删除成功！")
    else:
        print("线路不存在！")

if __name__ == '__main__':
    data = load_data()
    coordinate_data = load_coordinate_data()
    while(True):
        operation = input("请输入操作（a:添加 d:删除 q:退出）：")
        if operation == 'q':
            break
        elif operation == 'a':
            add_line(data, coordinate_data)
        elif operation == 'd':
            delete_line(data)
        else:
            print("非法操作！")
    
    pre_process(DATA_PATH, FILE_PATH, COORDINATE_PATH)