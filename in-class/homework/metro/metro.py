from copy import deepcopy
import json
import os
import heapq
import datetime

class Station:
    def __init__(self, name, number, line, transfers=None, position=None):
        self.name = name
        self.number = number
        self.line = line
        self.transfers = deepcopy(transfers) if transfers is not None else [] # 防止引用传递
        self.position = deepcopy(position) if position is not None else [] # (经度，纬度)
        
    def add_transfers(self, transfer):
        self.transfers.append(transfer)
        
    def set_position(self, position):
        self.position = deepcopy(position)
    
    def __str__(self):
        return f'{self.name} {self.number} {self.line} {self.transfers}'
    
    def __repr__(self):
        return f'{self.name} {self.number} {self.line} {self.transfers}'
        
class Line:
    def __init__(self, name, number, top_speed, average_speed, color):
        self.name = name
        self.number = number
        self.top_speed = top_speed
        self.average_speed = average_speed
        self.color = color
        
    def __str__(self):
        return f'{self.name} {self.number} {self.top_speed} {self.average_speed} {self.color}'
    
    def __repr__(self):
        return f'{self.name} {self.number} {self.top_speed} {self.average_speed} {self.color}'
    
class Edge:
    def __init__(self, to, time, std_time, distance, direction):
        self.to = to
        self.time = time
        self.std_time = std_time
        self.distance = distance
        self.direction = direction

class Metro:
    def __init__(self, data_path, file_path, coordinate_path, transfer_time = 300, transfer_inf = 300000):
        self.data_path = data_path
        self.file_path = file_path
        self.coordinate_path = coordinate_path
        self.load_data()
        self.transfer_time = transfer_time
        self.transfer_inf = transfer_inf
    
    def convert_time(self, second): # 获得分钟数
        second = (second//self.transfer_inf)*self.transfer_time + (second%self.transfer_inf) # 转换为实际时间
        miniute = second // 60
        return miniute

    def cal_price(self, starts, ends) -> float: # 计算票价
        _, came_from, end = self.find_route(starts, ends, mode=2, time_mode=0)
        
        current = end # current只代表数字编号
        all_dis = 0
        air_dis = 0
        PEK_price = 0
        PKX_price = 0
        while came_from[current][0] != -1: # 从终点开始回溯整条路径
            edge = came_from[current][1]
            all_dis += edge.distance
            if self.is_airport_edge(edge):
                air_dis += edge.distance
                if self.edge_line(edge).name == '首都机场线':
                    PEK_price = 25.0
                else:
                    f_name = self.stations[came_from[current][0]].name
                    t_name = self.stations[current].name
                    if t_name == '大兴新城': f_name, t_name = t_name, f_name
                    
                    if t_name == '草桥': PKX_price += 10.0
                    elif t_name == '大兴机场': PKX_price += 25.0
            
            current = came_from[current][0]
        air_price = PEK_price + PKX_price
        
        if all_dis == air_dis and all_dis != 0: # 全程在机场线
            return air_price, all_dis
        
        distance = float(all_dis - air_dis) / 1000 # 将距离转换为浮点数并转换为公里
        
        if distance <= 6:
            price = 3.0
        elif distance <= 12:
            price = 4.0
        elif distance <= 22:
            price = 5.0
        elif distance <= 32:
            price = 6.0
        else:
            extra_distance = distance - 32
            extra_price = (extra_distance // 20) + 1
            price = 6.0 + extra_price
            
        return price + air_price, all_dis
    
    def is_airport_station(self, station_nums): # 判断是否为必须经过机场线的站
        for station_num in station_nums:
            if self.stations[station_num].name in ['首都机场', '大兴机场', '大兴新城', "3号航站楼", "2号航站楼",]:
                return True
        return False
    
    def is_airport_edge(self, edge): # 判断是否为机场线的边
        return (self.edge_line(edge).name in ['首都机场线', '大兴机场线']) and edge.time != -1
    
    def edge_line(self, edge):
        return self.lines[self.stations[edge.to].line]

    def find_route(self, starts, ends, mode=0, time_mode = 0): # 使用dijkstra算法查找最短路，mode=0为最短时间，mode=1为最少换乘，mode=2为最短路程
        distance = [float('inf') for _ in range(700)] # 经过特殊处理的时间
        meters = [float('inf') for _ in range(700)] # 距离
        visited = [False for _ in range(700)]
        came_from = [(-1, '') for _ in range(700)]
        is_airport_path = self.is_airport_station(starts+ends) # 是否必须经过机场线
        
        if mode == 2: # 根据模式选择关键字和非关键字
            key_dis = meters
            other_dis = distance
        else:
            key_dis = distance
            other_dis = meters
        
        # 堆优化
        heap = []
        for num in starts: # 注意到起点有多个（从换乘站上车）
            key_dis[num] = 0
            other_dis[num] = 0
            heapq.heappush(heap, (key_dis[num], num))
        
        while len(heap)>0: # 堆不为空
            _, current = heapq.heappop(heap)
            if current in ends: # 到达代表终点的任意一站
                return distance, came_from, current
            
            if visited[current]:
                continue
            visited[current] = True
            for edge in self.edges[current]:
                to, dis = edge.to, edge.distance
                time = edge.time if time_mode == 0 else edge.std_time # 不同的时间计算方法
                if self.is_airport_edge(edge) and not is_airport_path: continue # 机场线太贵了，能不走就不走
                if edge.time == -1: # 换乘边
                    time = self.transfer_time if mode == 0 else self.transfer_inf
                
                if mode == 2: # 根据模式选择关键字和非关键字
                    key_w = dis
                    other_w = time
                else :
                    key_w = time
                    other_w = dis
                
                if visited[to]: continue
                    
                if key_dis[to] > key_dis[current] + key_w: # 更新关键字                   
                    key_dis[to] = key_dis[current] + key_w
                    came_from[to] = (current, edge)
                    other_dis[to] = other_dis[current] + other_w
                    heapq.heappush(heap, (key_dis[to], to))
    
    def print_route(self, came_from, end, distance, price, real_dis): 
        """返回路径字符串"""
        output = []
        
        # 获得系统时间
        current_time = datetime.datetime.now()
        current_time_str = current_time.strftime("%H:%M")
    
        if came_from[end][0] == -1:  # 无法到达
            output.append('非法路径！')
            return '\n'.join(output)
        
        route = [(end, '')]
        current = route[0][0]  # current只代表数字编号
        while came_from[current][0] != -1:
            route.insert(0, came_from[current])
            current = came_from[current][0]
        
        last_transfer_num = 0
        last_station = None
        p_h = 0 # 占位符个数
        for i in range(len(route)):
            station = self.stations[route[i][0]]
            if station.name == '占位符':
                p_h += 1
            dir = route[last_transfer_num][1].direction if i > 0 else ''
            
            if i == 0:  # 上车站
                output.append(f'在 {station.name} 上车，当前时间 {current_time_str}')
            elif i == len(route) - 1:
                period = distance[route[i][0]] - distance[route[last_transfer_num][0]]
                station_ammount = i - last_transfer_num
                if self.lines[station.line].name == '首都机场线': station_ammount -= p_h
                dir = dir if '航站楼' not in station.name else station.name  # 首都机场线特殊Y形结构
                
                output.append(f'在 {self.lines[station.line].name}（{dir}方向） 乘坐 {station_ammount} 站，耗时 {int(self.convert_time(period))} 分钟。')
                current_time += datetime.timedelta(minutes=int(self.convert_time(period)))
                current_time_str = current_time.strftime("%H:%M")
                output.append(f'在 {station.name} 下车，当前时间 {current_time_str}')  # 下车站
                output.append(f'\n总耗时 {int(self.convert_time(distance[route[i][0]] - distance[route[0][0]]))} 分钟，距离 {real_dis / 1000:.1f} 千米，票价 {price} 元。')
    
            if i > 0 and last_station.name == station.name:  # 输出换乘
                period = distance[route[i - 1][0]] - distance[route[last_transfer_num][0]]
                station_ammount = i - last_transfer_num - 1
                if self.lines[station.line].name == '首都机场线': station_ammount -= p_h
                output.append(f'在 {self.lines[last_station.line].name}（{dir}方向） 乘坐 {station_ammount} 站，耗时 {int(self.convert_time(period))} 分钟。')
                current_time += datetime.timedelta(minutes=int(self.convert_time(period)))
                current_time_str = current_time.strftime("%H:%M")
                output.append(f'在 {station.name} 换乘 {self.lines[station.line].name}，当前时间 {current_time_str}')
                last_transfer_num = i
            
            last_station = station
    
        return '\n'.join(output)
            
    def print_path(self, start_name, end_name, mode, time_mode):
        starts = self.station2number[start_name]
        ends = self.station2number[end_name]
        price, real_dis = self.cal_price(starts, ends) # 票价只和起点终点有关
        
        distance, came_from, end = self.find_route(starts, ends, mode, time_mode)
        return self.print_route(came_from, end, distance, price, real_dis), came_from, end
  
    def load_data(self): # 读取已经预处理好的数据
        if not os.path.exists(self.file_path): # 如果没有预处理好的数据，先进行预处理
            from pre_process import pre_process
            pre_process(self.data_path, self.file_path, self.coordinate_path)
        
        with open(self.file_path, 'r', encoding='utf-8') as file:
            data = json.load(file)
        
        self.stations = [Station(station[0], station[1], station[2], station[3], station[4]) for station in data['stations']]
        self.lines = [Line(line[0], line[1], line[2], line[3], line[4]) for line in data['lines']]
        
        self.station2number = data['station2number']
        self.line2number = data['line2number']
        self.edges = [[Edge(edge[0], edge[1], edge[2], edge[3], edge[4]) for edge in station_edges] for station_edges in data['edges']]
