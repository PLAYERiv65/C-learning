import geopandas as gpd
import matplotlib.pyplot as plt
from matplotlib import rcParams
from matplotlib.colors import ListedColormap, BoundaryNorm
from matplotlib.widgets import TextBox, Button
from metro import Metro
import time

MAP_PATH = './beijing.json'
METRO_PATH = './data.json'

# 设置字体和负号显示
rcParams['font.sans-serif'] = ['SimSun']  # 使用宋体
rcParams['axes.unicode_minus'] = False  # 解决负号显示问题

class MapViewer:
    def __init__(self, map_path, metro: Metro):
        self.map_path = map_path
        self.metro = metro
        
        # 小组件、布局部分
        self.fig, self.ax = plt.subplots()
        self.fig.set_size_inches(12, 8)
        self.fig.canvas.manager.set_window_title('地铁线路查询')
        self.startx, self.starty = 0, 0
        self.mPress = False
        self.search_mode = 0  # 初始模式为最短时间
        self.click_mode = 0  # 初始模式为设置起点
        self.time_mode = 0  # 初始模式为优化算法
        
        self.init_button()
        
        # 禁用坐标轴
        self.ax.set_xticks([])
        self.ax.set_yticks([])
        self.ax.set_xticklabels([])
        self.ax.set_yticklabels([])

        self.ax.set_position([0.37, 0.1, 0.65, 0.8])
        
        # 保存高亮路径的绘图对象
        self.highlight_start = None
        self.highlight_end = None
        self.highlight_path = []

    def init_button(self):
        self.start_box_ax = self.fig.add_axes([0.05, 0.85, 0.1, 0.05])
        self.start_box = TextBox(self.start_box_ax, '起点', initial="")

        self.end_box_ax = self.fig.add_axes([0.2, 0.85, 0.1, 0.05])
        self.end_box = TextBox(self.end_box_ax, '终点', initial="")

        self.output_box_ax = self.fig.add_axes([0.05, 0.35, 0.35, 0.45])
        self.output_box = TextBox(self.output_box_ax, '方案', initial="")
        self.disable_textbox_events(self.output_box)  # 禁用输出框的事件处理

        self.query_button_ax = self.fig.add_axes([0.05, 0.25, 0.1, 0.05])
        self.query_button = Button(self.query_button_ax, '查询')
        self.query_button.on_clicked(self.update_output)
        
        self.clear_highlight_button_ax = self.fig.add_axes([0.2, 0.25, 0.1, 0.05])
        self.clear_highlight_button = Button(self.clear_highlight_button_ax, '清除高亮')
        self.clear_highlight_button.on_clicked(self.clear_highlight)

        self.search_mode_button_ax = self.fig.add_axes([0.05, 0.15, 0.1, 0.05])
        self.search_mode_button = Button(self.search_mode_button_ax, '最短时间')
        self.search_mode_button.on_clicked(self.switch_search_mode)
        
        self.click_mode_button_ax = self.fig.add_axes([0.2, 0.15, 0.1, 0.05])
        self.click_mode_button = Button(self.click_mode_button_ax, '设置起点')
        self.click_mode_button.on_clicked(self.switch_click_mode)
        
        self.time_mode_button_ax = self.fig.add_axes([0.05, 0.05, 0.1, 0.05])
        self.time_mode_button = Button(self.time_mode_button_ax, '优化算法') # 切换时间计算模式
        self.time_mode_button.on_clicked(self.switch_time_mode)

    def update_output(self, event):
        """更新画面"""
        start_name = self.start_box.text
        end_name = self.end_box.text
        
        if start_name not in self.metro.station2number or end_name not in self.metro.station2number:
            output_text = "站点不存在！"
            self.output_box.set_val(output_text)
            return
        else:
            output_text, came_from, end = self.metro.print_path(start_name, end_name, mode=self.search_mode, time_mode=self.time_mode)  # 根据当前模式获得输出文本
        
        # 清除之前的高亮路径
        self.clear_highlight(None)
    
        current = end
        transfer_list = []
        while came_from[current][0] != -1:
            f_station = self.metro.stations[came_from[current][0]]
            t_station = self.metro.stations[current]
            current = came_from[current][0]
            
            if f_station.name == t_station.name:  # 跳过同一站点的连边
                transfer_list.append(f_station)
                continue
            # 高亮连边
            self.highlight_edge(f_station, t_station)
        # 先画边再画点，保证点在边的上方
        self.highlight_station(self.metro.stations[current], 0)  # 高亮起点
        self.highlight_station(self.metro.stations[end], 1)  # 高亮终点
        for station in transfer_list:
            self.highlight_station(station, 2)  # 高亮换乘站
        
        self.output_box.set_val(output_text)
        
        # 更新画布
        self.fig.canvas.draw_idle()
        
    def highlight_station(self, station, type):  # 高亮起点、终点、换乘站
        # 清除之前的高亮
        if type == 0 and self.highlight_start is not None:
            self.highlight_start.remove()
            self.highlight_start = None
        elif type == 1 and self.highlight_end is not None:
            self.highlight_end.remove()
            self.highlight_end = None
            
        color_map = {
            0: 'go',
            1: 'ro',  
            2: 'bo'
        }
        # 绘制点
        marker, = self.ax.plot(
            station.position[0],
            station.position[1],
            color_map[type],
            markersize=10 if type == 2 else 15,  # 设置点的大小
            markeredgewidth=2,
            markeredgecolor='black'  # 设置边缘颜色
        )
        
        if type == 0:
            self.highlight_start = marker
        elif type == 1:
            self.highlight_end = marker
        elif type == 2:
            self.highlight_path.append(marker)
        
        self.fig.canvas.draw_idle()  # 更新画布
        
    def highlight_edge(self, f_station, t_station):  # 高亮连边
        from_pos = f_station.position
        to_pos = t_station.position
        
        color = self.metro.lines[t_station.line].color
        # 根据经纬度画出站点，根据颜色连边
        line, = self.ax.plot(
            [from_pos[0], to_pos[0]],
            [from_pos[1], to_pos[1]],
            color=color,
            linewidth=4  # 设置线条宽度
        )
        self.highlight_path.append(line)
        
    def clear_highlight(self, event):
        """清除高亮"""
        if self.highlight_start:  # 清除起点
            self.highlight_start.remove()
            self.highlight_start = None
        if self.highlight_end:  # 清除终点
            self.highlight_end.remove()
            self.highlight_end = None
        
        for obj in self.highlight_path: # 清除高亮边
            obj.remove()
        self.highlight_path.clear()
        self.output_box.set_val("")
        self.fig.canvas.draw_idle()

    def switch_search_mode(self, event):
        """切换模式"""
        self.search_mode = (self.search_mode + 1) % 3  # 在0, 1, 2之间循环
        search_mode_names = ["最短时间", "最少换乘", "最短距离"]
        self.search_mode_button.label.set_text(f'{search_mode_names[self.search_mode]}')
        self.search_mode_button.ax.figure.canvas.draw_idle()  # 手动触发按钮部分的重绘
        
    def switch_click_mode(self, event):
        """切换模式"""
        self.click_mode = (self.click_mode + 1) % 2  # 在0, 1之间循环
        click_mode_names = ["设置起点", "设置终点"]
        self.click_mode_button.label.set_text(f'{click_mode_names[self.click_mode]}')
        self.click_mode_button.ax.figure.canvas.draw_idle()  # 手动触发按钮部分的重绘
        
    def switch_time_mode(self, event):
        """切换模式"""
        self.time_mode = (self.time_mode + 1) % 2  # 在0, 1之间循环
        time_mode_names = ["优化算法", "标准算法"]
        self.time_mode_button.label.set_text(f'{time_mode_names[self.time_mode]}')
        self.time_mode_button.ax.figure.canvas.draw_idle()  # 手动触发按钮部分的重绘

    def call_move(self, event):
        """处理鼠标拖动事件，实现图形的平移。"""
        if event.name == 'button_press_event':  # 鼠标左键按下
            axtemp = event.inaxes
            if axtemp and event.button == 1:
                self.mPress = True
                self.startx, self.starty = event.xdata, event.ydata
                self.press_time = time.time()  # 记录按下的时间
    
        elif event.name == 'button_release_event':
            self.mPress = False
            release_time = time.time()  # 记录释放的时间
            duration = release_time - self.press_time  # 计算按下的持续时间
    
            if duration < 0.2:  # 如果持续时间小于0.2秒，认为是单击事件
                self.on_click(event)
    
        elif event.name == 'motion_notify_event':
            axtemp = event.inaxes
            if axtemp and event.button == 1 and self.mPress:
                mx, my = event.xdata - self.startx, event.ydata - self.starty
                x_min, x_max = axtemp.get_xlim()
                y_min, y_max = axtemp.get_ylim()
                w, h = x_max - x_min, y_max - y_min
    
                axtemp.set(xlim=(x_min - mx, x_min - mx + w))  # 重新设置显示范围
                axtemp.set(ylim=(y_min - my, y_min - my + h))
                self.fig.canvas.draw_idle()
                
    def on_click(self, event):
        """处理鼠标单击事件，检测是否点击了某个站点"""
        if event.inaxes != self.ax:
            return

        click_x, click_y = event.xdata, event.ydata
        for station_name, station_num in self.metro.station2number.items():
            station = self.metro.stations[station_num[0]]
            if station.name == '占位符': continue
            station_x, station_y = station.position

            # 检查点击位置是否在站点的范围内
            if abs(click_x - station_x) < 0.002 and abs(click_y - station_y) < 0.002:
                if self.click_mode == 0: # 设置起点
                    self.start_box.set_val(station_name)
                elif self.click_mode == 1: # 设置终点
                    self.end_box.set_val(station_name)
                self.highlight_station(station, self.click_mode) # 高亮起点或终点
                break

    def call_scroll(self, event):
        """处理鼠标滚轮事件，实现图形的缩放。"""
        axtemp = event.inaxes
        if axtemp:
            x_min, x_max = axtemp.get_xlim()
            y_min, y_max = axtemp.get_ylim()
            w, h = x_max - x_min, y_max - y_min
            curx, cury = event.xdata, event.ydata
            curXposition = (curx - x_min) / w
            curYposition = (cury - y_min) / h

            scale_factor = 1.15 if event.button == 'down' else 1/1.15 # 向下滚还是向上滚
            w, h = w * scale_factor, h * scale_factor

            newx = curx - w * curXposition
            newy = cury - h * curYposition
            axtemp.set(xlim=(newx, newx + w)) # 重新设置显示范围
            axtemp.set(ylim=(newy, newy + h))
            self.fig.canvas.draw_idle()

    def connect_event(self):
        """绑定相关事件"""
        self.fig.canvas.mpl_connect('scroll_event', self.call_scroll)
        self.fig.canvas.mpl_connect('button_press_event', self.call_move)
        self.fig.canvas.mpl_connect('button_release_event', self.call_move)
        self.fig.canvas.mpl_connect('motion_notify_event', self.call_move)

    def disable_textbox_events(self, textbox):
        """禁用 TextBox 的事件处理"""
        textbox.disconnect_events()

    def show_background(self):
        """显示城市地图"""
        # 读取地理数据
        city = gpd.read_file(self.map_path)
        city = city.sort_values(by='adcode')
        
        # 定义四色调色板
        colors = ['#FFBBBB', '#BBBBFF', '#FFFFBB']  # 红、蓝、黄
        cmap = ListedColormap(colors)

        # 定义每个颜色段的边界
        boundaries = [0, 6, 12, 16]
        norm = BoundaryNorm(boundaries, cmap.N, clip=True)

        # 绘制地图
        city.plot(
            ax=self.ax,
            column="subFeatureIndex",
            cmap=cmap,
            norm=norm,
            edgecolor="gray"
        )

    def show_metro(self):
        """显示地铁线路"""
        for from_num, f_edges in enumerate(self.metro.edges): # 连边
            for edge in f_edges:
                line = self.metro.edge_line(edge)
                to_num = edge.to
                if "航站楼" in self.metro.stations[from_num].name and "航站楼" in self.metro.stations[to_num].name:
                    continue # 首都机场线特殊结构
                from_pos = self.metro.stations[from_num].position
                to_pos = self.metro.stations[to_num].position
                
                color = line.color
                # 根据经纬度画出站点，根据颜色连边
                self.ax.plot(
                    [from_pos[0], to_pos[0]],
                    [from_pos[1], to_pos[1]],
                    color=color
                )
        
        for station_name in self.metro.station2number: # 画出车站
            station = self.metro.stations[self.metro.station2number[station_name][0]]
            if station.name == '占位符': continue
            is_transfer = True if len(station.transfers)>0 else False
            
            self.ax.plot(
                station.position[0],
                station.position[1],
                'bo' if is_transfer else 'go'
            )
    
    def show(self):
        """显示图形"""
        self.connect_event()
        self.show_background()
        self.show_metro()
        plt.show()