#!/usr/bin/env python3
import os, argparse

paths = []

for root, dirs, files in os.walk("./"):
    program_file = "" 

    if '.DS_Store' in files:
        files.remove('.DS_Store')
    if root.startswith("./.") or root == "./" or len(files) == 0:
        continue
    for file in files:
        if not file.endswith('test') and not file.endswith('in') and not file.endswith('exe') and '.' in file:
            program_file = file
            break

    if '.git' in dirs:
        dirs.remove('.git')
    if '.vscode' in dirs:
        dirs.remove('.vscode')
    
    path = f'{root}/{program_file}'
    with open(path, 'r') as f:
        try:
            if len(f.read().strip().splitlines()) != 0:
                paths.append(root.split("/")[1:])
        except:
            pass

completed = dict()
keep = set()

parser = argparse.ArgumentParser(description='Finds solved problems.')
parser.add_argument('-l')
parser.add_argument('-y')
parser.add_argument('-d')
args = parser.parse_args()

keep = set()
defaults = list(map(set, zip(*paths)))

if args.l != None:
    keep |= set(args.l.split(','))
else:
    keep |= defaults[0]
if args.y != None:
    keep |= set(args.y.split(','))
else:
    keep |= defaults[1]
if args.d != None:
    keep |= set(args.d.split(','))
else:
    keep |= defaults[2]


for lang, year, day in paths:
    if lang not in keep or year not in keep or day not in keep: continue
    if lang not in completed:
        completed[lang] = dict()
    if year not in completed[lang]:
        completed[lang][year] = []
    completed[lang][year].append(day)

total = 0

for lang in completed:
    if lang not in keep: continue
    print(lang)
    for i, year in enumerate(sorted(completed[lang])):
        if (i+1 == len(completed[lang])):
            print('└───' + year)
        else:
            print('├───' + year)
        for j, day in enumerate(sorted(completed[lang][year])):
            start = " " if i+1 == len(completed[lang]) else "│"
            if (j+1 == len(completed[lang][year])):
                print(start + '   └───' + day)
            else:
                print(start + '   ├───' + day)
            total += 1
    print()

print(f"Solved: {total}")
            