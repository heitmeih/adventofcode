#!/usr/bin/env python3
 extracting the data from the input file
with open('day1.test','r') as f:
    captcha = f.read()

part1_sum = 0
part2_sum = 0

for i in range(-1, len(captcha) - 1):
    if captcha[i] == captcha[i + 1]:
        part1_sum += int(captcha[i])

    if captcha[i] == captcha[(i + int(len(captcha) / 2)) % len(captcha)]:
        part2_sum += int(captcha[i])

print('Part 1:', part1_sum)
print('Part 2:', part2_sum)

# one line solutions for each
# print('Part 1:', sum([int(captcha[i]) for i in range(-1, len(captcha) - 1) if captcha[i] == captcha[i + 1]]))
# print('Part 2:', sum([int(captcha[i]) for i in range(-1, len(captcha) - 1) if captcha[i] == captcha[(i + int(len(captcha) / 2)) % len(captcha)]]))