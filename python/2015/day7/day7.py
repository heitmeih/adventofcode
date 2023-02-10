#!/usr/bin/env python3
#i'll be honest, i may have just copied this from elsewhere
import operator, re

with open('day7.in', 'r') as infile:
    data = infile.readlines()

#i'm pretty sure the hex is to force operations to be like 16 bit, since python doesn't let you control that stuff
monops = {
    'NOT': lambda x : ~x & 0xFFFF,
}

#very smart move. i often forget that dictionarys are basically identical js objects and can even have functions
binops = {
    'AND': operator.and_,
    'OR': operator.or_,
    'LSHIFT': operator.lshift,
    'RSHIFT': operator.rshift,
}

machine = {}

for line in data:
    line = line.strip()

    #i had no clue that this was something you could do
    m = (
        re.match(r'(\w+) -> (\w+)', line)
        or re.match(r'(\w+) (\w+) (\w+) -> (\w+)', line)
        or re.match(r'(\w+) (\w+) -> (\w+)', line)
    ).groups()

    machine[m[-1]] = m[:-1]

def evaluate(register_or_value):
    try:
        return int(register_or_value)
    except:
        return run(register_or_value)

def run(register, state = {}):
    if not register in state:
        command = machine[register]

        if len(command) == 1:
            value, = command
            state[register] = evaluate(value)

        elif len(command) == 2:
            monop, input = command
            state[register] = monops[monop](evaluate(input))

        elif len(command) == 3:
            input_1, binop, input_2 = command
            state[register] = binops[binop](evaluate(input_1), evaluate(input_2))

    return state[register]


print(run('a'))
#literally just put this result into b in the input file to get part 2
#even though i didn't make this, i can learn from it