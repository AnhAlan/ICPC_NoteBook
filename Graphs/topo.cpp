// maxn = scc_cnt if use dag
const int maxn = 1e6 + 5;
bool check[maxn];
vector<int> topo;
void dfs_topo(int u){
    check[u] = true;
    //change adj or dag
    for(int v : dag[u]){
        if(!check[v]){ 
            dfs_topo(v);
        }
    }
    topo.push_back(u);
    //dfs -> reverse poto
}

