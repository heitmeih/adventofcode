// I'm making this with little experience and no internet, so this won't look pretty.
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Advent2021
{
    class Day12
    {
        static void Main(string[] args)
        {   
            var caves = new List<Cave>();
            foreach (string line in File.ReadAllLines("./day12.in"))
            {
                string[] connection = line.Split("-");
                Cave first = new Cave(connection[0]);
                Cave second = new Cave(connection[1]);

                if (!caves.Contains(first))
                {
                    caves.Add(first);
                }
                if (!caves.Contains(second))
                {
                    caves.Add(second);
                }

                if (second.Name != "start") caves[caves.IndexOf(first)].AddNeighbor(second);
                if (first.Name != "start") caves[caves.IndexOf(second)].AddNeighbor(first);
            }

            // foreach (var cave in caves)
            // {
            //     Console.Write($"{cave};{cave.IsSmall} = ");
            //     foreach (var n in cave.Neighbors)
            //     {
            //         Console.Write($"{n};{n.IsSmall} ");
            //     }
            //     Console.WriteLine();
            // }

            var pathfinder = new Pathfinder(caves);

            pathfinder.FindPaths(); 

            Console.WriteLine(pathfinder.NumPaths);
        }
    }
    class Pathfinder
    {
        private List<Cave> caves;
        private Queue<Route> queue;
        private int numPaths;

        public Pathfinder(List<Cave> caves)
        {
            this.caves = caves;
            queue = new Queue<Route>();
            queue.Enqueue(new Route(new Cave("start")));
        }

        public void FindPaths()
        {   
            //this whole time... the issue could have been resolve by doing a while loop instead of recursion...
            while (queue.Count() != 0) 
            {
                if (queue.Peek().Top().Name == "end")
                {
                    numPaths++;
                    queue.Dequeue();
                    continue;
                }
                foreach (Cave node in caves[caves.IndexOf(queue.Peek().Top())].Neighbors)
                {
                    if (!queue.Peek().IsNodeAllowed(node)) continue;
                    Route temp = new Route(queue.Peek());
                    temp.AddNode(node);
                    queue.Enqueue(temp);
                }
                queue.Dequeue();
            }
        }

        public int NumPaths
        {
            get { return numPaths; }
        }

    }
    class Route : IEquatable<Route>
    {
        private List<Cave> nodes;
        private string dupe;

        public Route()
        {
            nodes = new List<Cave>();
            dupe = "";
        }
        public Route(Route r) 
        {
            dupe = r.dupe;
            nodes = new List<Cave>(r.nodes);
        }
        public Route(Cave start) : this()
        {
            AddNode(start);
        }

        public Cave Top()
        {
            return nodes[nodes.Count()-1];
        }

        public void AddNode(Cave node)
        {
            nodes.Add(node);
            if (!HasDupe && node.IsSmall && nodes.Where(cave => cave.Equals(node)).Count() == 2)
            {
                dupe = node.Name;
            }
        }

        public bool IsNodeAllowed(Cave node)
        {
            if (!node.IsSmall) return true;
            return (!HasDupe || (HasDupe && node.Name != dupe && nodes.Where(cave => cave.Equals(node)).Count() != 1));
        }

        public virtual bool Equals(Route r)
        {
            return r.nodes.Equals(nodes);
        }

        public bool HasDupe
        {
            get { return dupe != ""; }
        }
        public List<Cave> Nodes
        {
            get { return nodes; }
        }
    }

    class Cave
    {
        private string name;
        private List<Cave> neighbors;

        public Cave(string name) 
        {
            this.name = "" + name;
            neighbors = new List<Cave>();
        }

        public void AddNeighbor(Cave n)
        {
            neighbors.Add(n);
        }

        public List<Cave> Neighbors
        {
            get { return neighbors; }
        }

        public bool IsSmall
        {
            get { return (name == name.ToLower()); }
        }

        public string Name
        {
            get { return name; }
        }

        public override string ToString()
        {
            return name;
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            
            return name == ((Cave) obj).name;
        }
        
        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
    }
}