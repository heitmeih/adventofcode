#!/usr/bin/env python3
infile = open("./day2.in", 'r')

tot_wrap_pap = 0
tot_ribbon = 0
for line in infile:
    l, w, h = map(int, line.split('x'))
    len_list = [l, w, h]
    len_list.remove(max(len_list))
    for side in len_list:
        tot_ribbon += side*2
    volume = l*w*h
    box = (2*l*w) + (2*w*h) + (2*h*l) + min([l*w, w*h, h*l])
    tot_ribbon += volume
    tot_wrap_pap += box

print(tot_wrap_pap, tot_ribbon)
infile.close()