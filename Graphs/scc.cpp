template<typename T>
struct Scc {
   const digraph<T> &g;
   int n;
   int timer = 0;
   int sccCnt = 0;
   vector<int> num, low, comp;
   vector<bool> inStack;
   vector<vector<int>> scc;
   stack<int> st;
   Scc(const digraph<T> &_g) : g(_g), n(_g.n){
      num.assign(n + 1, 0);
      low.assign(n + 1, 0);
      comp.assign(n + 1, 0);
      inStack.assign(n + 1, false);
      scc.resize(n + 1);
   }
   void dfs(int u) {
      num[u] = low[u] = ++timer;
      st.push(u);
      inStack[u] = true;
      for(int id : g.adj[u]) {
         int v = g.edges[id].to;
         if(!num[v]) {
               dfs(v);
               low[u] = min(low[u], low[v]);
         }
         else if(inStack[v]) {
               low[u] = min(low[u], num[v]);
         }
      }
      if(low[u] == num[u]) {
         ++sccCnt;
         while(true) {
               int v = st.top();
               st.pop();
               inStack[v] = false;
               comp[v] = sccCnt;
               scc[sccCnt].push_back(v);
               if(v == u) break;
         }
      }
   }
   void build_scc() {
      if(sccCnt > 0) return;
      for(int i = 1; i <= n; i++) {
         if(!num[i]) dfs(i);
      }
   }
   vector<vector<int>> build_dag() {
      build_scc();
      vector<vector<int>> dag(sccCnt + 1);
      for(int u = 1; u <= n; u++) {
         int a = comp[u];
         for(int id : g.adj[u]) {
               int v = g.edges[id].to;
               int b = comp[v];
               if(a != b) {
                  dag[a].push_back(b);
               }
         }
      }
      for(int i = 1; i <= sccCnt; i++) {
         sort(dag[i].begin(), dag[i].end());
         dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
      }
      return dag;
   }
};