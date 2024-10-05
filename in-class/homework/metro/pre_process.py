import json
import csv
import re
from metro import Line, Station, Edge

def load_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        return json.load(file)
    
def cal_time(distance, average_speed) -> float: # 计算时间
    # 转换浮点数
    distance = float(distance)
    average_speed = float(average_speed)/3.6 # km/h -> m/s
    return distance / average_speed

def cal_std_time(distance, top_speed) -> float: # 计算课件要求时间
    # 转换浮点数
    distance = float(distance)
    average_speed = float(top_speed)/3.6/2 # km/h -> m/s -> 2倍
    return distance / average_speed + 60 # 考虑站停时间
    
def organize(file_path, coordinate_path): # 得到地铁站、地铁线路的编号，建立邻接表
    metro_data = load_file(file_path)
    lines_data = metro_data['Lines']
    
    station_set = set()
    stations = []
    station2number = {}
    lines = []
    line2number = {}
    edges = [[] for _ in range(700)] # 邻接表
    
    num = 0
    for line_data in lines_data: # 遍历地铁线路并获得数据
        line_num = len(line2number)
        line = Line(line_data['Name'], line_num, line_data['Top_Speed'], line_data['Average_Speed'], line_data['Color'])
        lines.append(line)
        line2number[line_data['Name']] = line_num
        
        last_station = None
        first_station_name = None
        first_station_num = None # 特判环线
        line_data['Distances'].insert(0, 0) # 第一个站特判， 因为边比点少1
        is_circle = (line_data['Stations'][0] == line_data['Stations'][-1]) # 判断是否环线
        
        if not is_circle:
            direction = [line_data['Stations'][0], line_data['Stations'][-1]]
        
        for i, (station_name, distance) in enumerate(zip(line_data['Stations'], line_data['Distances'])): # 遍历地铁站并获得数据
            found = False
            if station_name not in station_set: # 使用set去重地铁站名
                station_set.add(station_name)
                station2number[station_name] = [num]
            else: # 重复
                for station_num in station2number[station_name]:
                    if stations[station_num].line == line_num: found = station_num
                if not found: 
                    station2number[station_name].append(num) # 换乘站
            
            if found: # 重复
                station = stations[found]
                num -= 1
            else:
                station = Station(station_name, num, line_num) # 不去重地铁站，实现类似分层图的效果
                stations.append(station)
                
            if first_station_name is None:
                first_station_name = station_name
                first_station_num = num
            
            if last_station is not None:
                if is_circle: # 特判环线的方向
                    direction = [last_station.name, station.name]
                time = cal_time(distance, line_data['Average_Speed'])
                std_time = cal_std_time(distance, line_data['Top_Speed'])
                if '航站楼' in last_station.name: # 首都机场线具有Y形结构，需要特判方向
                    direction[1] = '北新桥'
                if '航站楼' in station.name: 
                    direction[0] = '北新桥'
                edges[last_station.number].append(Edge(station.number, time, std_time, distance, direction[1]))
                edges[station.number].append(Edge(last_station.number, time, std_time, distance, direction[0]))
            
            last_station = station
            num += 1
        
    for station in stations: # 添加换乘站
        for num in station2number[station.name]:
            if num != station.number:
                station.add_transfers(num)
                edges[station.number].append(Edge(num, -1, -1, 0, '换乘'))
                
    stations = get_coordinates(coordinate_path, stations, station2number)
    
    return stations, lines, station2number, line2number, edges

def get_coordinates(file_path, stations, station2number):
    with open(file_path, mode='r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        for row in reader:
            if row['城市'] == '北京市':
                # 使用正则表达式去除括号和括号内的内容
                station_name = re.sub(r'\(.*?\)', '', row['名称']).strip()
                if station_name not in station2number: continue
                
                longitude, latitude = map(float, row['经纬度'].split(','))
                for num in station2number[station_name]:
                    stations[num].set_position((longitude, latitude))
                
    return stations

def save_data(stations, lines, station2number, line2number, edges, file_path):
    data = {
        'stations': [(station.name, station.number, station.line, station.transfers, station.position) for station in stations],
        'lines': [(line.name, line.number, line.top_speed, line.average_speed, line.color) for line in lines],
        'station2number': station2number,
        'line2number': line2number,
        'edges': [[(edge.to, edge.time, edge.std_time, edge.distance, edge.direction) for edge in station_edges] for station_edges in edges]
    }
    
    with open(file_path, 'w', encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=4) # 更为美观的排版

def pre_process(data_path, save_path, coordinate_path):
    stations, lines, station2number, line2number, edges = organize(data_path, coordinate_path)
    save_data(stations, lines, station2number, line2number, edges, save_path)