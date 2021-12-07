#!/usr/bin/env python3
with open('day1.in', 'r') as f:
    data = f.read().split('\n')

fuel_sum = 0

def find_req_fuel(mass):
    return (int(mass) // 3) - 2

def fake_recursive_fuel(value):
    result = 0
    fuel = find_req_fuel(value)
    while fuel > 0:
        result += fuel
        fuel = find_req_fuel(fuel)
    return result

for mass in data:
    fuel = fake_recursive_fuel(mass)
    fuel_sum += fuel


#this was added in 2021 bc part 1 solution is not here for some reason
#literally requires negative brainpower tho
print('Part 1:', sum([(int(mass) // 3)-2 for mass in data]))

print(f'Sum: {fuel_sum}')

#one line version
print(sum(map(fake_recursive_fuel, data)))