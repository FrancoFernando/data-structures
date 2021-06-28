class dsu{
        
  vector<int> parent;
  vector<int> size;
  
  public:
  
  dsu(int n) 
  {
      parent.resize(n);
      size.resize(n,1);
      iota(parent.begin(), parent.end(), 0);
  }

  /*
  int find(int x) {
      
      while(parent[numToPos[x]] != numToPos[x]) {
          x = parent[numToPos[x]];
      }
      return numToPos[x];
  }
  */
 
  int find(int x) {
      
      if (parent[x] == x) return x;
      return parent[x] = find(parent[x]);
  }
  
  void unite(int x, int y) {
      
      int rootX = find(x);
      int rootY = find(y);
      
      if (rootX == rootY) return;
      
      if (size[rootX] < size[rootY]) swap(rootX, rootY);
      size[rootX] += size[rootY];
      parent[y] = rootX;
      if(size[rootX] > max_size) max_size = size[rootX];
  }
  
  int maxSize() {
      return max_size;
  }
};