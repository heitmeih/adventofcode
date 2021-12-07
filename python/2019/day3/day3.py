#!/usr/bin/env python3
import time as t
with open('day3.in') as f:
    data = f.read().split('\n')

timer = t.time()

#central port will be at (0, 0)

def add_point(lis, diction):
    # takes a list of tuples (formatted [((x, y), steps), ((x, y), steps), ... ]
    for tup in lis:
        if tup[0] not in diction:
            diction[tup[0]] = tup[1]

wire_paths = {1 : {}, 2: {}}
path = 0
for wire in data:
    steps = 0
    path += 1
    prev_coord = (0, 0)
    wire_directions = wire.split(',')
    for instruction in wire_directions:
        direction = instruction[0]
        distance = int(instruction[1:])
        if direction == 'U':
            add_point([((prev_coord[0], prev_coord[1] + i), steps + i) for i in range(1, distance + 1)], wire_paths[path])
            prev_coord = (prev_coord[0], prev_coord[1] + distance)
        elif direction == 'D':
            add_point([((prev_coord[0], prev_coord[1] - i), steps + i) for i in range(1, distance + 1)], wire_paths[path])
            prev_coord = (prev_coord[0], prev_coord[1] - distance)
        elif direction == 'R':
            add_point([((prev_coord[0] + i, prev_coord[1]), steps + i) for i in range(1, distance + 1)], wire_paths[path])
            prev_coord = (prev_coord[0] + distance, prev_coord[1])
        else:
            add_point([((prev_coord[0] - i, prev_coord[1]), steps + i) for i in range(1, distance + 1)], wire_paths[path])
            prev_coord = (prev_coord[0] - distance, prev_coord[1])
        steps += distance

intersections = wire_paths[1].keys() & wire_paths[2].keys()

print('Part 1:', min([abs(x) + abs(y) for x, y in intersections]))
print('Part 2:', min([wire_paths[1].get(coord) + wire_paths[2].get(coord) for coord in intersections]))
print('Time taken:', round(t.time() - timer, 3), 'seconds')