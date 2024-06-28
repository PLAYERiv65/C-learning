from gui import MAZE
from astar import astar
import pygame

def main():
    pygame.font.init()
    width = int(input("Please input the width of the maze: "))
    height = int(input("Please input the height of the maze: "))
    maze = MAZE(width, height)
    #running
    running = True
    while running:
        maze.draw()
        running = maze.handle_event()
        if maze.mode == 1:
            running = astar(maze)
            maze.mode = 0

    pygame.quit()

if __name__ == "__main__":
    main()