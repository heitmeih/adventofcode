#!/usr/bin/env python3
#import solution

with open('./day3.in', 'r') as file:
    data = file.read().splitlines()

def get_common(bit, reversed = False):
    more_zeroes = bit.count('0') > bit.count('1')
    if reversed:
        return '1' if more_zeroes else '0'
    return '0' if more_zeroes else '1'

def bitwise_not(bits):
    return ''.join(map(lambda x: '1' if x == '0' else '0', bits))

def get_rating(data, reversed = False, bit_pos = 0):
    valid = list([x for x in data if x[bit_pos] == get_common(list(zip(*data))[bit_pos], reversed)])
    if len(valid) == 1: 
        return valid[0]
    return get_rating(valid, reversed, bit_pos + 1)


common_bits = ''.join(map(get_common, zip(*data)))
print(int(common_bits, 2) * int(bitwise_not(common_bits), 2))
print(int(get_rating(data), 2) * int(get_rating(data, True), 2))

