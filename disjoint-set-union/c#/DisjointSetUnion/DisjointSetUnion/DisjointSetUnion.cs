using System.Collections.Generic;
using System.Linq;

namespace DisjointSetUnion
{
    public class DisjointSetUnion
    {
        private readonly List<int> parent = new List<int>();
        private readonly List<int> size = new List<int>();

        public DisjointSetUnion(int n)
        {
            parent.AddRange(Enumerable.Range(0, n));
            size.AddRange(Enumerable.Repeat(0, n));
        }

        
        public int Find(int x) {

            while (parent[x] != x)
            {
                x = parent[x];
                parent[x] = parent[parent[x]];
            }
            return parent[x];
        }
        
        /*
        //Recursive
        public int Find(int x)
        {

            if (parent[x] == x) return x;
            return parent[x] = Find(parent[x]);
        }
        */

        public void Unite(int x, int y)
        {

            int rootX = Find(x);
            int rootY = Find(y);

            if (rootX == rootY) return;

            if (size[rootX] < size[rootY]) (rootX, rootY) = (rootY, rootX);
            size[rootX] += size[rootY];
            parent[rootY] = rootX;
        }

        public bool Same(int x, int y)
        {
            return Find(x) == Find(y);
        }
    }
}
