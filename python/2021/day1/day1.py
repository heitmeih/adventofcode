#!/usr/bin/env python3
#import solution

with open('./day1.in', 'r') as file:
    data = list(map(int, file.read().splitlines()))

count1, count2 = (0, 0)

for x, y in zip(data[:-1], data[1:]):
    if y > x: count1 += 1

# does this even count as 'pythonic' any more...
for x, y in zip(map(sum, zip(data[:-3], data[1:-2], data[2:-1])), map(sum, zip(data[1:-2], data[2:-1], data[3:]))):
    if y > x: count2 += 1

print(count1, count2)