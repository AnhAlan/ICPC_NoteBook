const int maxn = 1e3;
int node[2*maxn];   
int pos[maxn];       
int fin[maxn];       
int cnt = 0;
int high[maxn];     

void dfs(int u,int par){
    node[++cnt] = u;
    pos[u] = cnt;    
    for(int v : adj[u]){
        if(v != par){
            high[v] = high[u] + 1;
            dfs(v,u);
            node[++cnt] = u; 
        }
    }
    fin[u] = cnt;     
}

int MinHigh(int u,int v){
    return high[u] < high[v] ? u : v;
}
//2^log >= maxn
const int LOG = 10;
int minH[2*maxn][LOG]; 
void build_lca(){
    for(int i=1;i<=cnt;i++){
        minH[i][0] = node[i];
    }

    for(int j=1;j<LOG;j++){
        for(int i=1;i<= cnt - MASK(j)+1;i++){
            minH[i][j] = MinHigh(minH[i][j-1],minH[i + MASK(j-1)][j-1]);
        }
    }
}

int lca(int u,int v){
    int pu = pos[u];
    int pv = pos[v];
    if(pu > pv){
        swap(pu,pv);
    }
    int k = 31 - __builtin_clz(pv-pu+1); 
    return MinHigh(minH[pu][k],minH[pv-MASK(k)+1][k]);
}

