using System;
using System.IO;

namespace Advent2021
{
    class Day2
    {
        static void Main(string[] args)
        {
            string[] lines = File.ReadAllLines("./day2.in");

            int aim = 0, x = 0, depth = 0;

            foreach (string line in lines) 
            {
                int magnitude = Int32.Parse(line.Split(" ")[1]);
                switch (line[0]) 
                {
                    case 'f':
                        x += magnitude;
                        depth += aim * magnitude;
                        break;
                    case 'd':
                        aim += magnitude;
                        break;
                    case 'u':
                        aim -= magnitude;
                        break;
                }
            }
            Console.WriteLine($"Part 1: {aim * x}\nPart 2: {x * depth}");
        }
    }
}