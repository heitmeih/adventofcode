#!/usr/bin/env python3
import time as t
start_time = t.time() # timing operation for fun

# open the file and extracting the data into a list of lines
with open('day1.in', 'r') as file:
    data = file.read().split('\n')

# turning the data from str to int
freqs = [int(num) for num in data]
# another method: freqs = list(map(int, data))

# this can done in one line, but we need the int form of data (freqs) more than once
# one line: print(sum([int(num) for num in data]))
print('Part 1:', sum(freqs))

#using a set because it's faster to check than a list
freqs_reached = set()
freq_sum = 0
searching = True

#while loop is used to keep looping through freqs until a freq_sum appears twice
while searching:
    for freq in freqs:
        freqs_reached.add(freq_sum) #adding the sum to the set freqs_reached
        freq_sum += freq 
        if freq_sum in freqs_reached:
            searching = False
            break #stops the for loop

print('Part 2:', freq_sum)

print(f'\nTime taken: {round(t.time() - start_time, 5)} seconds') # prints time taken