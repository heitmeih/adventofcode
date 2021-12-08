#!/usr/bin/env python3
import hashlib

increment = -1
result = 1

print("\n*The purpose of this program is to generate results for Day 4 of Advent of Code*")

string = str(input("\nInput a string/code: "))
mode = input("\nInput a number of zeros (e.g. '000' or '00000') ")
print('')

while result != mode:
    increment += 1
    try:
        result = (hashlib.md5((string + str(increment)).encode()).hexdigest()[:len(mode)])
        print(result, increment)
    except:
        result = 1

print("\nCode:", string,"\nNumber:", increment, "\n\nResult:", string+str(increment), "\n")