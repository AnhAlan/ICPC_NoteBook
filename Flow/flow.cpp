template <typename T>
class Flow {
public:
   static constexpr T EPS = (T) 1e-9;
   struct Edge {
      int from, to;
      T cap;
      T f;
      T cost; 
   };
   vector<vector<int>> g;
   vector<Edge> edges;
   int n, st, fin;
   T flow;

   Flow(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {
      assert(1 <= st && st <= n && 1 <= fin && fin <= n && st != fin);
      g.resize(n + 1);
      flow = 0;
   }

   void reset() {
      for (Edge &e : edges) {
         e.f = 0;
      }
      flow = 0;
   }

   int add(int from, int to, T forward_cap, T backup_cap = 0, T edge_cost = 0) {
      assert(1 <= from && from <= n && 1 <= to && to <= n);
      int id = (int) edges.size();
      g[from].push_back(id);
      edges.push_back({from, to, forward_cap, 0, edge_cost});
      g[to].push_back(id + 1);
      edges.push_back({to, from, backup_cap, 0, -edge_cost}); 
      return id;
   }
};