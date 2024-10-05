import heapq
import pygame
from time import sleep
from gui import MAZE
#曼哈顿距离
def distance(p1, p2):
    return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1])
#回溯路径，记录点的原类型并返回
def backtrace(maze, current, came_from):
    stack = []
    while current is not None:
        stack.append(maze.get_type(current))
        maze.set_type(current, maze.ROUTE)
        current = came_from[current]
    return stack
#回溯路径，恢复值
def backtrace2(maze, current, came_from, stack):
    while current is not None:
        maze.set_type(current, stack.pop())
        current = came_from[current]
        
def output_path(current, came_from): # 输出路径
    stack = []
    while current is not None:
        stack.append(current)
        current = came_from[current]
    for node in stack[::-1]:
        print(node)
        
def all_route(maze: MAZE, current, came_from): # 获得所有路径
    pre = current
    while current is not None:
        next = came_from[current]
        maze.set_type(pre, 7)
        if next is not None: maze.set_type(next, 7)
        
        if found_path(maze, current, 0): # 是否有路径
            maze.set_type(current, 7)
            dfs_route(maze, current, 0, current)
            maze.set_type(current, maze.ROUTE)
            maze.route_num += 1
        
        maze.set_type(pre, maze.ROUTE)
        if next is not None: maze.set_type(next, maze.ROUTE)
        
        pre = current
        current = came_from[current]
        
def found_path(maze: MAZE, current, len): # 先得知是否有路径
    current_type = maze.get_type(current)
    if current_type == maze.END or current_type == maze.ROUTE or current_type == maze.OTHER_ROUTE: 
        if len>1: return True
        elif len==1: return False
    maze.set_type(current, 7)
    
    result = False
    for dy, dx in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        neighbor = (current[0]+dy, current[1]+dx)
        type = maze.get_type(neighbor)
        if type == -1 or type == maze.OBSTACLE or type == 7: continue
        if found_path(maze, neighbor, len+1):
            maze.set_type(current, current_type)
            return True  
    maze.set_type(current, current_type)
    return result
            
def dfs_route(maze: MAZE, current, len, fa): # 深度优先搜索路径
    if current is None:
        return False

    is_path = False
    new_path = False
    for dy, dx in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        neighbor = (current[0]+dy, current[1]+dx)
        type = maze.get_type(neighbor)
        if type == -1 or type == maze.OBSTACLE or neighbor == fa: continue # 不合法的部分
        if (type == maze.ROUTE or type == maze.OTHER_ROUTE or type == maze.END or type == 7): # 确定形成路径
            if len>2: is_path = True
            continue
        
        maze.set_type(neighbor, 7)
        
        if new_path: maze.route_num += 1 # 新路径编号
        
        if dfs_route(maze, neighbor, len+1, current):
            new_path = True
            is_path = True
            maze.set_route(neighbor, maze.route_num) # 新的路径类型
        elif new_path:
            maze.route_num -= 1
    
    return is_path   
    
def wait_for_mouse_click():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                return True
        sleep(0.01)  # 避免过度占用 CPU

def astar(maze :MAZE):
    found = False
    start = maze.start
    end = maze.end
    open_list = []
    closed_list = set()
    g = {start: 0}
    f = {start: distance(start, end)}
    came_from = {start: None}  # 记录每个节点的多个前驱
    heapq.heappush(open_list, (f[start], -g[start], start))
    maze.set_type(start, maze.SEARCHED)
    maze.set_distance(start, 0)

    running = True
    while open_list and running and maze.mode == 1:
        _, _, current = heapq.heappop(open_list)
        running = maze.handle_event()

        if not found:
            sleep(0.02)
            # 从当前节点回溯到起点，将路径上的节点标记为特殊颜色,同时存储原来的值
            stack = backtrace(maze, current, came_from)
            maze.set_type(current, maze.START)
            maze.draw()

            if current == end:
                found = True
                print("Path found:")
                output_path(current, came_from)
                isrunning = wait_for_mouse_click()
                if not isrunning:
                    return False
                #清空distance，置零所有非障碍节点
                #maze.clean()
                #running = False
                continue 

            backtrace2(maze, current, came_from, stack)

        closed_list.add(current)
        for dy, dx in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            neighbor = (current[0]+dy, current[1]+dx)
            if maze.get_type(neighbor) == -1: continue
            
            # 如果邻居是墙体或者已经在关闭列表中，则跳过
            if maze.get_type(neighbor) == maze.OBSTACLE or neighbor in closed_list:
                continue
            # 如果邻居不在开放列表中，则将其加入开放列表
            if neighbor not in g or g[current]+1 < g[neighbor]:
                g[neighbor] = g[current]+1
                maze.set_distance(neighbor, g[neighbor])
                maze.set_type(neighbor, maze.SEARCHED)
                if neighbor not in came_from:
                    came_from[neighbor] = current # 记录前驱
                f[neighbor] = g[neighbor] + distance(neighbor, end)
                heapq.heappush(open_list, (f[neighbor], -g[neighbor], neighbor))
    
    if found:
        maze.route_num = 1
        all_route(maze, end, came_from) # 寻找所有可能路径
        maze.set_type(end, maze.START)
        maze.draw() # 更新画面
        wait_for_mouse_click()
    else:
        print("No path found.")
        wait_for_mouse_click()
    maze.clean()
    return True