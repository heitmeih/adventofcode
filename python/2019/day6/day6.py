#!/usr/bin/env python3
import re

with open('day6.in') as f:
    data = f.read().split('\n')

orbits = []
orbit_counts = {'COM': 0}
borders = {'COM': []}

for line in data:
    orbits.append(re.search(r"(\w{,3})\)(\w{,3})", line).groups())

while len(orbits) > 0:
    for a_orbit, b_orbit in orbits:
        if b_orbit not in orbit_counts and a_orbit in orbit_counts:
            orbit_counts[b_orbit] = orbit_counts[a_orbit] + 1

            borders[a_orbit].append(b_orbit)
            if b_orbit not in borders:
                borders[b_orbit] = []
            borders[b_orbit].append(a_orbit)

            orbits.remove((a_orbit, b_orbit))

def check_next(next_orb, q, dis):
    
    if len(q) != 0:
        check_next(q.pop(0), q, dis)

def find_distance(start, end):
    queue = [start]
    distances = {start: 0}

    for next_orb in queue:
        for orbit in borders[next_orb]:
            if orbit not in distances:
                distances[orbit] = distances[next_orb] + 1
                queue.append(orbit)
                
    return distances[end] - 2

print(sum(orbit_counts.values()), find_distance('YOU', 'SAN'))