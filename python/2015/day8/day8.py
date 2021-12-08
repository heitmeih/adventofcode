#!/usr/bin/env python3
with open("./day8.in", 'r') as infile:
    data = infile.readlines()

character_num = 0
string_num = 0

# Part 1

for line in data:
    for char in line:
        if char != '\n':
            character_num += 1
    string = line[1:len(line) - 2]
    ignore = []
    for index in range(len(string)):
        if index not in ignore:
            if string[index] == '\\':
                if index != len(string) - 1:
                    if string[index + 1] != 'x':
                        ignore.append(index + 1)
                    else:
                        ignore.append(index + 1)
                        ignore.append(index + 2)
                        ignore.append(index + 3)
                    string_num += 1
            else:
                string_num += 1

print("\nPart One:", character_num - string_num)

character_num = 0
string_num = 0

# Part 2

for line in data:
    for char in line[:len(line) - 1]:
        if char in ['\\', '"']:
            character_num += 2
        else:
            character_num += 1
    character_num += 2
    string = line[1:len(line) - 2]
    ignore = []
    for char in line:
        if char != '\n':
            string_num += 1

print("\nPart Two:", character_num - string_num, '\n')

#out of curiousity...
with open('./day8.in', 'r') as f:
    text = f.read().splitlines()

code, mem, escaped = 0, 0, 0

#found out about .maketrans thanks to stackoverflow :)
translations = {
    "-":  r"\-",
    "]":  r"\]",
    "\\": r"\\",
    "^":  r"\^",
    "$":  r"\$",
    "*":  r"\*",
    ".":  r"\.",
    '"': r'\"'
}

for line in text:
    code += len(line)
    mem += len(eval(line))
    escaped += len(f'"{line.translate(str.maketrans(translations))}"')

print(code - mem)
print(escaped - code)
