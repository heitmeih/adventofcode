#!/usr/bin/env python3
import sys

with open('day5.in', 'r') as f:
    data = f.read().split(',')
data = list(map(int, data))

'''
KEY:
99 = terminate
01 = add
02 = multiply
05 = jump-if-true
06 = jump-if-false
07 = less-than
08 = equals
3 = input
4 = output

mode 0 = position mode
mode 1 = immediate mode
'''

def get_modes(opcode):
    opcode = str(opcode).zfill(5)
    # (opcode function, mode1, mode2, mode3)
    return (int(opcode[len(opcode) - 1]), int(opcode[len(opcode) - 3]), int(opcode[len(opcode) - 4]), int(opcode[len(opcode) - 5]))

pointer = 0


while pointer <= len(data) - 1:
    opcode = data[pointer]
    modes = get_modes(opcode)
    if opcode == 99:
        print('terminating...')
        sys.exit()
    elif modes[0] in [3,4]:
        if modes[0] == 3:
            index = data[pointer + 1]
            inp = int(input('What is your input? '))
            data[index] = inp
        else:
            if modes[1] == 1:
                print('testing:', data[pointer + 1])
            else:
                print('testing:', data[data[pointer + 1]])
        pointer += 2
    else:
        if modes[1] == 1:
            input_1 = data[pointer + 1]
        else:
            input_1 = data[data[pointer + 1]]
        if modes[2] == 1:
            input_2 = data[pointer + 2]
        else:
            input_2 = data[data[pointer + 2]]
        if modes[0] == 1:
            output = data[pointer + 3]
            #opcode 1: addition
            data[output] = input_1 + input_2
            pointer += 4
        elif modes[0] == 2:
            output = data[pointer + 3]
            #opcode 2: multiply
            data[output] = input_1 * input_2
            pointer += 4
        elif modes[0] == 5:
            # opcode 5: jump if true
            pointer += 3
            if input_1 != 0:
                pointer = input_2
        elif modes[0] == 6:
            # opcode 6: jump if false
            pointer += 3
            if input_1 == 0:
                pointer = input_2
        elif modes[0] == 7:
            # opcode 7: less than
            output = data[pointer + 3]
            if input_1 < input_2:
                data[output] = 1
            else:
                data[output] = 0
            pointer += 4
        else:
            # opcode 8: equals
            output = data[pointer + 3]
            if input_1 == input_2:
                data[output] = 1
            else:
                data[output] = 0
            pointer += 4
