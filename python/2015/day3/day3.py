#!/usr/bin/env python3
# day three is missing... i'll just do it right now then
with open('./day3.in', 'r') as file:
    data = file.read()

def get_visited(route):
    x, y = 0, 0
    visited = {(0, 0)}
    for d in route:
        if d == '^': #north
            y += 1
        elif d == 'v': #south
            y -= 1
        elif d == '>': #east
            x += 1
        else: #west
            x -= 1
        visited.add((x, y))
    return visited

print(len(get_visited(data)), len(get_visited(data[::2]) | get_visited(data[1::2])))