#!/usr/bin/env python3
def read_file(filename):
    floor = 0
    pos = 0
    infile = open(filename, 'r')
    for line in infile:
        for letter in line:
            if floor == -1:
                return(pos)
            if letter == '(':
                floor += 1
                pos += 1
            else:
                floor -= 1
                pos += 1
    infile.close()
    return floor

print(read_file('./day1.in'))