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
        maze.set_type(current, maze.CELL_TYPES["ROUTE"])
        current = came_from[current]
    return stack
#回溯路径，恢复值
def backtrace2(maze, current, came_from, stack):
    while current is not None:
        maze.set_type(current, stack.pop())
        current = came_from[current]
    
def wait_for_mouse_click():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                return True
        sleep(0.01)  # 避免过度占用 CPU

def astar(maze :MAZE):
    start = maze.start
    end = maze.end
    open_list = []
    closed_list = set()
    g = {start: 0}
    f = {start: distance(start, end)}
    came_from = {start: None}  # 记录每个节点的父节点
    heapq.heappush(open_list, (f[start], -g[start], start))
    maze.set_type(start, maze.CELL_TYPES["SEARCHED"])
    maze.set_distance(start, 0)

    running = True
    while open_list and running and maze.mode == 1:
        #更新画面，显示当前状态
        sleep(0.02)
        running = maze.handle_event()
        _, _, current = heapq.heappop(open_list)
        # 从当前节点回溯到起点，将路径上的节点标记为特殊颜色,同时存储原来的值
        stack = backtrace(maze, current, came_from)
        maze.set_type(current, maze.CELL_TYPES["START"])
        maze.draw()

        if current == end:
            isrunning = wait_for_mouse_click()
            if not isrunning:
                return False
            #清空distance，置零所有非障碍节点
            maze.clean()
            running = False
            continue 

        backtrace2(maze, current, came_from, stack)

        closed_list.add(current)
        for i, j in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if maze.is_coordinate_in((current[0]+i, current[1]+j)):
                neighbor = (current[0]+i, current[1]+j)
                # 如果邻居是墙体或者已经在关闭列表中，则跳过
                if maze.get_type(neighbor) == maze.CELL_TYPES["OBSTACLE"] or neighbor in closed_list:
                    continue
                # 如果邻居不在开放列表中，则将其加入开放列表
                if neighbor not in g or g[current]+1 < g[neighbor]:
                    g[neighbor] = g[current]+1
                    maze.set_distance(neighbor, g[neighbor])
                    maze.set_type(neighbor, maze.CELL_TYPES["SEARCHED"])
                    f[neighbor] = g[neighbor] + distance(neighbor, end)
                    came_from[neighbor] = current  # 记录 neighbor 的父节点是 current
                    heapq.heappush(open_list, (f[neighbor], -g[neighbor], neighbor))
    maze.clean()
    return True