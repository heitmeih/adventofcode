using System;
using System.IO;

namespace Advent2021
{
    class Day1
    {
        static void Main(string[] args)
        {
            string[] lines = File.ReadAllLines("./day1.in");
            int[] data = new int[lines.Length];
            for (int i = 0; i < lines.Length; i++)
            {
                data[i] = Int32.Parse(lines[i]);
            }

            int p1Count = 0, p2Count = 0;

            for (int i = 0; i < data.Length - 1; i++) {       
                if (data[i] < data[i+1]) {
                    p1Count++;
                }
            }

            for (int i = 0; i < data.Length - 3; i++) {       
                if (data[i] + data[i+1] + data[i+2] < data[i+1] + data[i+2] + data[i+3]) {
                    p2Count++;
                }
            }

            Console.WriteLine("Part 1: {0}\nPart 2: {1}", p1Count, p2Count);
        }
    }
}