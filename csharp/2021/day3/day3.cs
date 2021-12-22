using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Advent2021
{
    class Day3
    {
        static void Main(string[] args)
        {
            List<string> lines = new List<string>(File.ReadAllLines("./day3.in"));

            string gamma = "";

            for (int c = 0; c < lines[0].Length; c++) 
            {
                gamma += getCommonBit(ref lines, c, x => x >= 0);
            }

            Console.WriteLine($"Part 1: {Convert.ToInt32(gamma, 2) * Convert.ToInt32(bitwiseNot(gamma), 2)}");
            Console.WriteLine($"Part 1: {Convert.ToInt32(getRating(lines, x => x >= 0), 2) * Convert.ToInt32(getRating(lines, x => x < 0), 2)}");
        }

        static string getRating(List<string> valid, Func<int, bool> compare, int bit = 0)
        {
            valid = valid.Where(line => line[bit] == getCommonBit(ref valid, bit, compare)).ToList();
            if (valid.Count == 1) return valid[0];
            return getRating(valid, compare, bit + 1);
        }

        static char getCommonBit(ref List<string> lines, int bit, Func<int, bool> compare) {
            int counter = 0;
            for (int r = 0; r < lines.Count; r++)
            {
                counter += (lines[r][bit] == '1') ? 1 : -1;
            }
            return (compare(counter)) ? '1' : '0';
        }

        static string bitwiseNot(string bin)
        {
            string result = "";
            foreach (char c in bin)
            {
                if (c == '1') 
                {
                    result += "0";
                } 
                else
                {
                    result += "1";
                }
            }
            return result;
        }
    }
}