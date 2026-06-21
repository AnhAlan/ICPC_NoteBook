template<typename T>
struct Hungarian{
   struct Edge{
      int to, rev;
      T cap, cost;
   };
   int n;
   vector<vector<Edge>> g;
   Hungarian(int _n): n(_n){
      g.assign(n, {});
   }
   void add(int from, int to, T cap, T cost){
      Edge a = {to, (int)g[t].size(), cap, cost};
      Edge b = {from, (int)g[s].size(), 0, -cost};
      g[s].push_back(a);
      g[t].push_back(b);
   }
   pair<T,T> min_cost_max_flow(int S,int Tt){
      T flow = 0;
      T cost = 0;
      vector<T> dist(n);
      vector<int> pv(n), pe(n);
      while(true){
         fill(dist.begin(), dist.end(), numeric_limits<T>::max() / 2);
         dist[S] = 0;
         vector<bool> inq(n,false);
         queue<int> q;
         q.push(S);
         inq[S] = true;
         while(!q.empty()){
            int v = q.front();
            q.pop();
            inq[v] = false;
               for(int i = 0; i < (int) g[v].size(); i++){
                  auto &e = g[v][i];
                  if(e.cap > 0 && dist[v] + e.cost < dist[e.to]){
                     dist[e.to] = dist[v] + e.cost;
                     pv[e.to] = v;
                     pe[e.to] = i;
                     if(!inq[e.to]){
                        inq[e.to] = true;
                        q.push(e.to);
                     }
                  }
               }
         }
         if(dist[Tt] == numeric_limits<T>::max() / 2) break;
         T add = numeric_limits<T>::max();
         for(int v = Tt; v != S; v = pv[v]){
            auto &e = g[pv[v]][pe[v]];
            add = min(add,e.cap);
         }
         for(int v = Tt; v != S; v = pv[v]){
            auto &e = g[pv[v]][pe[v]];
            e.cap -= add;
            g[v][e.rev].cap += add;
         }
         flow += add;
         cost += add * dist[Tt];
      }
      return {flow,cost};
   }
};