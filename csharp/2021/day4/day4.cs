using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Advent2021
{
    class Board
    {   
        private int[][] rawBoard;
        private bool[,] selected;

        public Board(string boardString)
        {
            rawBoard = boardString.Split("\n").Select(line => line.Split(" ").Where(c => c != "").Select(x => Int32.Parse(x)).ToArray()).ToArray();
            selected = new bool[5, 5];
        }

        public bool SelectNum(int num) 
        {
            for (int r = 0; r < 5; r++) 
                for (int c = 0; c < 5; c++) 
                    if (rawBoard[r][c] == num) 
                    {
                        selected[r, c] = true;
                        return isWinner();
                    }
            return false;
        }

        public bool isWinner() 
        {
            for (int i = 0; i < 5; i++)
                if ((selected[i, 0] && selected[i, 1] && selected[i, 2] && selected[i, 3] && selected[i, 4]) || 
                    (selected[0, i] && selected[1, i] && selected[2, i] && selected[3, i] && selected[4, i])) return true;
            return false;
        }

        public int Score 
        {
            get
            {
                int score = 0;
                for (int r = 0; r < 5; r++)
                    for (int c = 0; c < 5; c++)
                        if (!selected[r, c])
                            score += rawBoard[r][c];
                return score;
            }
        }
    }

    class Day4
    {
        static void Main(string[] args)
        {
            string[] raw = File.ReadAllText("./day4.in").Split("\n\n");

            int[] nums = raw[0].Split(",").Select(x => Int32.Parse(x)).ToArray();

            var boards = new List<Board>();
            for (int i = 1; i < raw.Length; i++) boards.Add(new Board(raw[i]));

            int initialCount = boards.Count;

            foreach (int n in nums) {
                for (int i = boards.Count - 1; i >= 0; i--) 
                {
                    if (boards[i].SelectNum(n)) 
                    {
                        if (boards.Count == initialCount || boards.Count == 1) 
                            Console.WriteLine(boards[i].Score * n);
                        boards.RemoveAt(i);
                    }
                }
            }
        }
    }
}