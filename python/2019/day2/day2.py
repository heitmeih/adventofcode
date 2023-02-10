#!/usr/bin/env python3
for noun in range(0, 100):
    for verb in range(0, 100):
        with open('day2.in', 'r') as f:
            data = f.read().split(',')
        data = list(map(int, data))
        data[1] = noun
        data[2] = verb
        for index in range(0, len(data), 4):
            #opcode is the number at every 4 places
            opcode = data[index]
            input_1 = data[data[index + 1]]
            input_2 = data[data[index + 2]]
            output = data[index + 3]
            if opcode == 99:
                #opcode 99: terminate
                break
            elif opcode == 1:
                #opcode 1: addition
                data[output] = input_1 + input_2
            else:
                #opcode 2: multiply
                data[output] = input_1 * input_2
        final_output = data[0]
        if noun == 12 and verb == 2: print(final_output)
        if final_output == 19690720:
            #exits the for loop is the final output is equal to the number given
            print(100 * noun + verb)
            break