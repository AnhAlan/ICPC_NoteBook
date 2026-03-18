const int maxn = 1e6 + 5;
bool check[maxn];
vector<int> poto;
void dfs(int u){
    check[u] = true;
    for(int v : luu[u]){
        if(!check[v]){ 
            dfs(v);
        }
    }
    poto.push_back(u);
    //dfs -> reverse poto
}

