import geopandas as gpd
import matplotlib.pyplot as plt
from matplotlib import rcParams
from matplotlib.colors import ListedColormap, BoundaryNorm
from matplotlib.widgets import TextBox, Button
from metro import Metro

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
        self.startx, self.starty = 0, 0
        self.mPress = False
        self.mode = 0  # 初始模式为最短时间
        
        self.start_box_ax = self.fig.add_axes([0.05, 0.8, 0.1, 0.05])
        self.start_box = TextBox(self.start_box_ax, '起点', initial="")

        self.end_box_ax = self.fig.add_axes([0.05, 0.7, 0.1, 0.05])
        self.end_box = TextBox(self.end_box_ax, '终点', initial="")

        self.output_box_ax = self.fig.add_axes([0.05, 0.35, 0.3, 0.3])
        self.output_box = TextBox(self.output_box_ax, '方案', initial="")
        self.disable_textbox_events(self.output_box)  # 禁用输出框的事件处理

        self.query_button_ax = self.fig.add_axes([0.05, 0.25, 0.1, 0.05])
        self.query_button = Button(self.query_button_ax, '查询')
        self.query_button.on_clicked(self.update_output)

        self.mode_button_ax = self.fig.add_axes([0.05, 0.15, 0.1, 0.05])
        self.mode_button = Button(self.mode_button_ax, '最短时间')
        self.mode_button.on_clicked(self.switch_mode)

        self.ax.set_position([0.37, 0.1, 0.65, 0.8])

    def update_output(self, event):
        """更新画面"""
        start_name = self.start_box.text
        end_name = self.end_box.text
        
        if start_name not in self.metro.station2number or end_name not in self.metro.station2number:
            output_text = "站点不存在！"
        else :
            output_text = self.metro.print_path(start_name, end_name, mode=self.mode)  # 根据当前模式获得输出文本
        
        self.output_box.set_val(output_text)

    def switch_mode(self, event):
        """切换模式"""
        self.mode = (self.mode + 1) % 3  # 在0, 1, 2之间循环
        mode_names = ["最短时间", "最少换乘", "最短距离"]
        self.mode_button.label.set_text(f'{mode_names[self.mode]}')
        self.mode_button.ax.figure.canvas.draw_idle()  # 手动触发按钮部分的重绘

    def call_move(self, event):
        """处理鼠标拖动事件，实现图形的平移。"""
        if event.name == 'button_press_event': # 鼠标左键按下
            axtemp = event.inaxes
            if axtemp and event.button == 1:
                self.mPress = True
                self.startx, self.starty = event.xdata, event.ydata

        elif event.name == 'button_release_event':
            self.mPress = False

        elif event.name == 'motion_notify_event':
            axtemp = event.inaxes
            if axtemp and event.button == 1 and self.mPress:
                mx, my = event.xdata - self.startx, event.ydata - self.starty
                x_min, x_max = axtemp.get_xlim()
                y_min, y_max = axtemp.get_ylim()
                w, h = x_max - x_min, y_max - y_min

                axtemp.set(xlim=(x_min - mx, x_min - mx + w)) # 重新设置显示范围
                axtemp.set(ylim=(y_min - my, y_min - my + h))
                self.fig.canvas.draw_idle()

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

            scale_factor = 1.1 if event.button == 'down' else 1/1.1 # 向下滚还是向上滚
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
        extra_pos = [116.6, 40.05] # 首都机场线特殊结构段
        for from_num, f_edges in enumerate(self.metro.edges): # 连边
            for edge in f_edges:
                line = self.metro.edge_line(edge)
                to_num = edge.to
                from_pos = self.metro.stations[from_num].position
                to_pos = self.metro.stations[to_num].position
                
                to_name = self.metro.stations[to_num].name
                if to_name == '2号航站楼' or to_name == '3号航站楼' or to_name == '三元桥':
                    from_pos = extra_pos # 首都机场线特殊结构段
                
                color = line.color
                # 根据经纬度画出站点，根据颜色连边
                self.ax.plot(
                    [from_pos[0], to_pos[0]],
                    [from_pos[1], to_pos[1]],
                    color=color
                )
        
        for station_name in self.metro.station2number: # 画出车站
            station = self.metro.stations[self.metro.station2number[station_name][0]]
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

if __name__ == '__main__':
    beijing_metro = Metro(METRO_PATH)
    viewer = MapViewer(MAP_PATH, beijing_metro)
    viewer.show()