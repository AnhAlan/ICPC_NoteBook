vector<int> poto;
void kahn(){
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(in[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        poto.push_back(u)
        for(int x : adj[u]){
            in[x]--;  
            if(in[x] == 0){ 
                q.push(x);
            }
        }
    }
    //assert(poto.size() != 0)
}

