#!/usr/bin/env python3
#import solution

with open('./day2.in', 'r') as file:
    data = [(line[0], int(line.split(' ')[1])) for line in file.read().splitlines()]

def part1(data):
    x, depth = 0, 0

    for dir, amount in data:
        if dir == 'f':
            x += amount
        elif dir == 'd':
            depth += amount
        else: # u
            depth -= amount

    print('Part 1:', x * depth)

def part2(data):
    x, depth, aim = 0, 0, 0

    for dir, amount in data:
        if dir == 'f':
            x += amount
            depth += aim * amount
        elif dir == 'd':
            aim += amount
        else: # u
            aim -= amount

    print('Part 2:', x * depth)

part1(data)
part2(data)