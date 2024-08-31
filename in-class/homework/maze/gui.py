"""MAZE 迷宫类"""
import pygame
import random

class MAZE:
    CELL_TYPES = {
        "EMPTY": 0,
        "OBSTACLE": 1,
        "START": 2,
        "END": 3,
        "ROUTE": 4,
        "SEARCHED": 5
    }

    def __init__(self, width=30, height=20):#加载初始网格
        self.screen = pygame.display.set_mode((width*20, height*20))
        self.width = width
        self.height = height
        self.grid = [[0 for _ in range(width)] for _ in range(height)]
        self.distance = [[-1 for _ in range(width)] for _ in range(height)]
        self.start = None
        self.end = None
        self.shift = 0
        self.mode = 0
        self.run_button = pygame.Rect(0, 0, 50, 20)  # 将按钮放在窗口的顶部
        self.reset_button = pygame.Rect(60, 0, 70, 20)
        self.generate_button = pygame.Rect(160, 0, 70, 20)
        self.font_dis = pygame.font.SysFont('Courier New', 12)
        self.font_button = pygame.font.Font(None, 36)

    def set_distance(self, node, d):
        self.distance[node[1]][node[0]] = d

    def deset(self, node):
        self.grid[node[1]][node[0]] = 0

    def get_type(self, node):
        return self.grid[node[1]][node[0]]

    def set_type(self, node, t):
        self.grid[node[1]][node[0]] = t

    def clean(self):
        self.start = None
        self.end = None
        for y in range(self.height-1):
            for x in range(self.width):
                if self.grid[y][x] != 1:
                    self.grid[y][x] = 0
                    self.distance[y][x] = -1

    def is_coordinate_in(self, node):
        return 0 <= node[0] < self.width and 0 <= node[1] < self.height-1
    
    def is_pixel_in(self, node):
        return 0 <= node[0] < self.width*20 and 0 <= node[1] < (self.height-1)*20
    
    def generate_maze(self):  # 使用随机深度优先搜索生成迷宫
        for y in range(self.height-1):#先全设为墙
            for x in range(self.width):
                self.grid[y][x] = 1
        directions = [(0, 2), (0, -2), (2, 0), (-2, 0)]  # 越过墙壁
        
        start = end = (0, 0)
        self.set_type(start, self.CELL_TYPES["EMPTY"])
        stack = [start]
        while stack:
            x, y = stack[-1]
            self.grid[y][x] = 1
            neighbors = []
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < self.width and 0 <= ny < self.height and self.grid[ny][nx] == self.CELL_TYPES["OBSTACLE"]:
                    neighbors.append((nx, ny))
            if neighbors:
                random.shuffle(neighbors)  # 打乱邻居的顺序
                nx, ny = neighbors[0]
                stack.append((nx, ny))
                self.grid[(y + ny) // 2][(x + nx) // 2] = self.CELL_TYPES["EMPTY"]
            else:
                stack.pop()
    
    def draw(self):#绘制网格
        #显示当前输入模式
        if self.shift == 0:
            pygame.display.set_caption("Set obstacle")
        elif self.shift == 1:
            pygame.display.set_caption("Set start")
        elif self.shift == 2:
            pygame.display.set_caption("Set end")
        #显示当前self.mode
        if self.mode == 1:
            pygame.display.set_caption("Running")
        # Run 按钮 font_button
        pygame.draw.rect(self.screen, (0, 255, 0), self.run_button)
        text = self.font_button.render("Run", True, (0, 0, 0))
        self.screen.blit(text, (0, 0))
        #reset按钮
        pygame.draw.rect(self.screen, (255, 0, 0), self.reset_button)
        text = self.font_button.render("Reset", True, (0, 0, 0))
        self.screen.blit(text, (60, 0))
        #generate按钮
        pygame.draw.rect(self.screen, (0, 0, 255), self.generate_button)
        text = self.font_button.render("Generate", True, (0, 0, 0))
        self.screen.blit(text, (160, 0))

        # 绘制网格，为按钮区留空间
        for y in range(self.height-1):
            for x in range(self.width):
                if self.grid[y][x] == 1:
                    color = (0, 0, 0)
                elif self.grid[y][x] == 2:
                    color = (0, 255, 0)
                elif self.grid[y][x] == 3:
                    color = (255, 0, 0)
                elif self.grid[y][x] == 4:
                    color = (0, 0, 255)
                elif self.grid[y][x] == 5:
                    color = (255, max(255-self.distance[y][x],0), 0)
                else:
                    color = (255, 255, 255)
                pygame.draw.rect(self.screen, color, (x*20, (y+1)*20, 20, 20))  # 将网格向下移动20像素
                # 显示距离
                if self.distance[y][x] != -1:
                    text = self.font_dis.render(str(self.distance[y][x]), True, (0, 0, 0))
                    text_width, text_height = self.font_dis.size(str(self.distance[y][x]))
                    cell_center_x = x * 20 + 10  # 单元格的中心 x 坐标
                    cell_center_y = (y + 1) * 20 + 15  # 单元格的中心 y 坐标
                    text_pos_x = cell_center_x - text_width / 2  # 文本的 x 坐标
                    text_pos_y = cell_center_y - text_height / 2  # 文本的 y 坐标
                    self.screen.blit(text, (text_pos_x, text_pos_y))
                

        pygame.display.flip()
    #处理键盘鼠标操作
    def handle_event(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                xx, yy = event.pos
                y -= 20
                x //= 20
                y //= 20

                if event.button == 1:#左键
                    #run 按钮
                    if self.run_button.collidepoint(xx, yy) and self.mode == 0:
                        if self.start is None or self.end is None:
                            print("Please select start point and end point first.")
                        else:
                            self.mode = 1
                    #reset 按钮
                    if self.reset_button.collidepoint(xx, yy):
                        self.mode = 0
                        self.__init__(self.width, self.height)
                    #generate 按钮
                    if self.generate_button.collidepoint(xx, yy) and self.mode == 0:
                        self.clean()
                        self.generate_maze()
            
                    if self.mode == 1 or not self.is_coordinate_in((x, y)):
                        continue

                    if self.shift == 0:
                        if self.grid[y][x] == 1 or self.grid[y][x] == 0:
                            self.grid[y][x] ^= 1  # 将当前位置的值取反
                    elif self.shift == 1:
                        if self.start is not None:
                            self.deset(self.start)
                        self.set_type((x,y), self.CELL_TYPES["START"]) 
                        self.start = (x, y)
                    elif self.shift == 2:
                        if self.end is not None:
                            self.deset(self.end)
                        self.set_type((x,y), self.CELL_TYPES["END"]) 
                        self.end = (x, y)

            elif event.type == pygame.MOUSEMOTION:
                if pygame.mouse.get_pressed()[0] and self.shift == 0:  # 检查鼠标左键是否被按下
                    x, y = event.pos
                    if not self.is_pixel_in((x, y)):
                        continue
                    self.grid[(y-20)//20][(x)//20] = 1
                    
            elif event.type == pygame.KEYDOWN:#shift循环切换
                if event.key == pygame.K_LSHIFT:
                    self.shift = (self.shift+1) % 3

        return True
