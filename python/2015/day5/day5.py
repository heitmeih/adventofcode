#!/usr/bin/env python3
#day 5 is missing as well, so i'll just do it now
import re

with open('./day5.in', 'r') as file:
    data = file.read().splitlines()

bad_strs = ['ab', 'cd', 'pq', 'xy']
vowels = 'aeiou'

# are you ready for the ultimate pythonic solution?????
print('Part 1:', sum([1 if sum([string.count(vowel) for vowel in vowels]) >= 3 and sum([string.count(bad) for bad in bad_strs]) == 0 and re.search(r'(\w)\1', string) else 0 for string in data]))

# how about this one???
print('Part 2:', sum([1 if re.search(r'(\w)\w\1', string) and re.search(r'(\w\w)\w*\1', string) else 0 for string in data]))

# ultimate one-line-only solution (excluding re import):
with open('./day5.in', 'r') as file: print('Part 1:', sum([1 if sum([string.count(vowel) for vowel in 'aeiou']) >= 3 and sum([string.count(bad) for bad in ['ab', 'cd', 'pq', 'xy']]) == 0 and re.search(r'(\w)\1', string) else 0 for string in file.read().splitlines()]), '\nPart 2:'.format(file.seek(0)), sum([1 if re.search(r'(\w)\w\1', string) and re.search(r'(\w\w)\w*\1', string) else 0 for string in file.read().splitlines()]))