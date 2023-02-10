#!/usr/bin/env python3

#simple point class because looking at p1[0] is unclear and annoying and stupid
class Point():

    def __init__(self, point):
        self.x = point[0]
        self.y = point[1]

    def __repr__(self):
        return f'({self.x}, {self.y})'        


class Line():

    def __init__(self, p1: tuple, p2: tuple):
        self.p1 = Point(p1)
        self.p2 = Point(p2)
    
    def is_cardinal(self):
        return self.p1.x == self.p2.x or self.p1.y == self.p2.y

    def draw_line(self, canvas):
        #because i'm a hack, I will copy my c++ solution
        if self.p1.x != self.p2.x:
            m = (self.p1.y - self.p2.y)/(self.p1.x - self.p2.x)
            f = lambda x: m*x + (self.p1.y - m*self.p1.x)
            for x in range(min(self.p1.x, self.p2.x), max(self.p1.x, self.p2.x) + 1):
                canvas[int(f(x))][x] += 1
        else:
            for y in range(min(self.p1.y, self.p2.y), max(self.p1.y, self.p2.y) + 1):
                canvas[y][self.p1.x] += 1
    
    def __repr__(self):
        return f'({self.p1}, {self.p2})'

def count_inter(canvas):
    count = 0
    for row in canvas:
        for num in row:
            if num >= 2:
                count += 1
    return count

with open('day5.in', 'r') as f:
    data = [Line(tuple(map(int, line.split(' ')[0].split(','))), tuple(map(int, line.split(' ')[2].split(',')))) for line in f.read().splitlines()]

canvas_size = 1000

canvas = [[0 for _ in range(canvas_size)] for _ in range(canvas_size)]

for line in data:
    if line.is_cardinal(): 
        line.draw_line(canvas)

print('Part 1:', count_inter(canvas))

for line in data:
    if not line.is_cardinal(): 
        line.draw_line(canvas)

print('Part 2:', count_inter(canvas))

# for l in canvas: print(" ".join(map(str, l)))