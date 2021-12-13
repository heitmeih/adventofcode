#!/usr/bin/env python3
#import solution

class Board():

    def __init__(self, board):
        self.board = tuple(board)
        self.chosen = list(list(False for _ in range(5)) for _ in range(5))
    
    def __repr__(self):
        return str(self.board)

    def has_won(self):
        for line in self.chosen:
            if all(line):
                return True
        for line in zip(*self.chosen):
            if all(line):
                return True
        return False
    
    def choose(self, num: int):
        for r, row in enumerate(self.board):
            for c, col in enumerate(row):
                if num == col:
                    self.chosen[r][c] = True
                    return self.has_won()
        #print(self.chosen)
    
    def sum_unchosen(self):
        s = 0
        for r, row in enumerate(self.board):
            for c, col in enumerate(row):
                if not self.chosen[r][c]:
                    s += col
        return s


with open('day4.in', 'r') as f:
    split = f.read().split("\n\n")
    nums = list(map(int, split[0].split(',')))
    boards = []
    for board in split[1:]:
        b = []
        for line in board.splitlines():
            b.append(tuple(map(int, filter(lambda x: x != '', line.split(' ')))))
        boards.append(Board(b))

start_len = len(boards)

for num in nums:
    for board in boards:
        if board.choose(num):
            if len(boards) == start_len or len(boards) == 1:
                print(board.sum_unchosen() * num)
    boards = list(filter(lambda b: not b.has_won(), boards))