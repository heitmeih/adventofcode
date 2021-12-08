#!/usr/bin/env python3
#i originally did this in two files, so i'm just splitting them into functions
filename = 'day6.in'

def part1():
    infile = open(filename, 'r')

    on_sum = 0

    lights = [[False] * 1000 for i in range(1000)]

    def update_lights(m):
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                if m == 'toggle':
                    lights[x][y] = not lights[x][y]
                elif m == 'turn' and on:
                    lights[x][y] = True
                else:
                    lights[x][y] = False

    for line in infile:
        on = False
        off = False

        split_line = line.split(' ')
        if split_line[0] == 'turn':
            mode = "turn"
            if split_line[1] == 'on':
                on = True
            elif split_line[1] == 'off':
                off = True
            x1, y1 = map(int, split_line[2].split(','))
            x2, y2 = map(int, split_line[4].split(','))
        elif split_line[0] == 'toggle':
            mode = "toggle"
            x1, y1 = map(int, split_line[1].split(','))
            x2, y2 = map(int, split_line[3].split(','))

        update_lights(mode)

    for x in range(1000):
            for y in range(1000):
                if lights[x][y]:
                    on_sum += 1

    print(on_sum)

    infile.close()

def part2():
    infile = open(filename, 'r')

    on_sum = 0

    lights = [[0] * 1000 for i in range(1000)]

    def update_lights(m):
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                if m == 'toggle':
                    lights[x][y] += 2
                elif m == 'turn' and on:
                    lights[x][y] += 1
                elif m == 'turn' and off and lights[x][y] > 0:
                    lights[x][y] -= 1

    for line in infile:
        on = False
        off = False

        split_line = line.split(' ')
        if split_line[0] == 'turn':
            mode = "turn"
            if split_line[1] == 'on':
                on = True
            elif split_line[1] == 'off':
                off = True
            x1, y1 = map(int, split_line[2].split(','))
            x2, y2 = map(int, split_line[4].split(','))
        elif split_line[0] == 'toggle':
            mode = "toggle"
            x1, y1 = map(int, split_line[1].split(','))
            x2, y2 = map(int, split_line[3].split(','))

        update_lights(mode)

    for x in range(1000):
            for y in range(1000):
                on_sum += lights[x][y]

    print(on_sum)

    infile.close()


part1()
part2()