using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Advent2021
{   
    struct Point
    {
        public int x, y;
        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    class Line 
    {
        public Point p1, p2;
        public Line(int x1, int y1, int x2, int y2) {
            p1 = new Point(x1, y1);
            p2 = new Point(x2, y2);
        }
        
        public bool IsCardinal
        {
            get { return ( IsVertical || p1.y == p2.y); }
        }

        public bool IsVertical
        {
            get { return (p1.x == p2.x); }
        }

        public int Slope
        {
            get
            {
                if (!IsVertical) return (p2.y-p1.y)/(p2.x-p1.x);
                return 0;
            }
        }

        public int MinX
        {
            get { return Math.Min(p1.x, p2.x); }
        }

        public int MinY
        {
            get { return Math.Min(p1.y, p2.y); }
        }

        public int MaxX
        {
            get { return Math.Max(p1.x, p2.x); }
        }

        public int MaxY
        {
            get { return Math.Max(p1.y, p2.y); }
        }
    }

    class Canvas
    {
        private int[,] plane;
        int size;

        public Canvas()
        {   
            size = 2000;
            plane = new int[size, size];
        }

        public void DrawLine(Line l)
        {   
            if (!l.IsCardinal) // is diagonal
            {   
                for (int y = (l.Slope > 0) ? l.MinY : l.MaxY, x = l.MinX; x < l.MaxX; y += l.Slope, x++)
                    plane[y, x]++;
            }
            else if (l.IsVertical)
            {
                for (int y = l.MinY; y <= l.MaxY; y++)
                    plane[y, l.p1.x]++;
            }
            else 
            {
                for (int x = l.MinX; x <= l.MaxX; x++)
                    plane[l.p1.y, x]++;
            }
        }

        public int CountOverlap()
        {   
            int count = 0;
            foreach (int num in plane)
                if (num >= 2)
                    count++;
            return count;
        }
        
    }

    class Day5
    {
        static void Main(string[] args)
        {   
            var lines = new List<Line>();
            var canvas = new Canvas();

            foreach (string line in File.ReadAllLines("./day5.in")) 
            {
                var parsed = line.Split(" -> ").Select(t => t.Split(',').Select(x => Int32.Parse(x)).ToArray()).ToArray();
                lines.Add(new Line(parsed[0][0], parsed[0][1], parsed[1][0], parsed[1][1]));
            }

            foreach (Line line in lines)
                if (line.IsCardinal)
                    canvas.DrawLine(line);

            Console.WriteLine($"Part 1: {canvas.CountOverlap()}");

            foreach (Line line in lines)
                if (!line.IsCardinal)
                    canvas.DrawLine(line);
            
            Console.WriteLine($"Part 2: {canvas.CountOverlap()}");
        }
    }
}