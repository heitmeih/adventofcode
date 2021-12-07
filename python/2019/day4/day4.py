#!/usr/bin/env python3
with open('day4.in', 'r') as f:
    range_nums = [int(num) for num in f.read().split('-')]

test = '111133'

def has_adjacent(password):
    password = str(password)
    for i in range(1, len(password) - 2):
        if i == 1 and password[i - 1] == password[i] and password[i] != password[i + 1]: # checks beginning of password
            return True
        elif password[i - 1] != password[i] and password[i] == password[i + 1] and password[i + 1] != password[i + 2]: # checks middle of password
            return True
        elif i == len(password) - 3 and password[i] != password[i + 1] and password[i + 1] == password[i + 2]: # checks end of password
            return True
    return False

def no_decrease(password):
    password = str(password)
    for i in range(len(password) - 1):
        if int(password[i]) > int(password[i + 1]):
            return False
    return True

possible_password_num = 0


for num in range(range_nums[0], range_nums[1]):
    if has_adjacent(num) and no_decrease(num):
        possible_password_num += 1

#only solves part 2; part 1 was lost to the void
print(possible_password_num)
