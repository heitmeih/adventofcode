#!/usr/bin/env python3
import sys # this will be used later

#open the file and extract the data into a list of lines
with open('day2.in', 'r') as f:
    data = f.read().split('\n')

def get_letter_count(letter, string):
    # returns the number of times letter appears in string
    # NOTE: this can be done with string.count(letter) but i didn't know that when I made it
    count = 0
    for let in string:
        if letter == let:
            count += 1
    return count

def check_mostly_equal(string1, string2):
    # checks if two strings are equal if one character has been removed from both strings at the same index
    for i in range(0, len(string1)):
        cstring_1 = string1[:i] + string1[i+1:]
        cstring_2 = string2[:i] + string2[i+1:]
        if cstring_1 == cstring_2:
            return (True, cstring_1)
    return (False, None)

num_of_2 = 0
num_of_3 = 0

for line in data:
    has_3 = False
    has_2 = False
    for letter in set(line):
        num_of_letter = get_letter_count(letter, line)
        if num_of_letter == 2 and not has_2:
            num_of_2 += 1
            has_2 = True
        elif num_of_letter == 3 and not has_3:
            num_of_3 += 1
            has_3 = True

checksum = num_of_2 * num_of_3
print('Part 1:', checksum)

for id_1 in data:
    for id_2 in data:
        checked = check_mostly_equal(id_1, id_2)
        if checked[0] and id_1 != id_2:
            print('Part 2:', checked[1])
            sys.exit()