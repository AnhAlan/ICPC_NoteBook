template<typename T>
struct centroid_tree {
   forest<T> &g;
   vector<int> sz;
   vector<int> par;
   vector<bool> used;
   vector<vector<pair<int,int>>> path;
   centroid_tree(forest<T> &_g) : g(_g) {
      int n = g.n;
      sz.resize(n + 1);
      par.assign(n + 1, -1);
      used.assign(n + 1, false);
      path.assign(n + 1, {});
   }
   void dfs_sz(int u, int p) {
      sz[u] = 1;
      for (int id : g.adj[u]) {
         int v = g.edges[id].from ^ g.edges[id].to ^ u;
         if (v == p || used[v]) continue;
         dfs_sz(v, u);
         sz[u] += sz[v];
      }
   }
   int dfs_centroid(int u, int p, int total) {
      for (int id : g.adj[u]) {
         int v = g.edges[id].from ^ g.edges[id].to ^ u;
         if (v == p || used[v]) continue;
         if (sz[v] > total / 2){
            return dfs_centroid(v, u, total);
         }
      }
      return u;
   }
   void dfs_path(int u, int p, int cen, int dist) {
      path[u].push_back({cen, dist});
      for (int id : g.adj[u]) {
         int v = g.edges[id].from ^ g.edges[id].to ^ u;
         if (v == p || used[v]) continue;
         dfs_path(v, u, cen, dist + 1);
      }
   }
   void build(int u, int p) {
      dfs_sz(u, -1);
      int c = dfs_centroid(u, -1, sz[u]);
      par[c] = p;
      used[c] = true;
      dfs_path(c, -1, c, 0);
      for (int id : g.adj[c]) {
         int v = g.edges[id].from ^ g.edges[id].to ^ c;
         if (used[v]) continue;
         build(v, c);
      }
   }
};