const int maxn = 1e3;
struct trienode{
    int child[2];
    int cnt;
    trienode(){
        child[0] = child[1] = -1;
        cnt = 0;
    }
};

trienode node[maxn];
int root = 0;
int cnt_node = 1;
int create(){
    //node[cnt_node] = trienode();
    return cnt_node++;
}
//add binary
void insert(int k){
    int cur = root;
    node[cur].cnt++;
    for(int i=3;i>=0;i--){
        int b = bit(k,i);
        if(node[cur].child[b] == -1){
            node[cur].child[b] = create();
        }
        cur = node[cur].child[b];
        node[cur].cnt++;
    }
}

/*
    To find the minimum number in the trie:
    - At each bit position from high to low:
        + Prefer going to the child with bit 0 (because min number has more 0s)
        + If child 0 does not exist, go to child 1
    - If we go to child 1, set the corresponding bit in ans:
        ans |= MASK(i)
*/

int getmin(){
    int cur = root;
    int ans = 0;
    for(int i=3;i>=0;i--){
        if(node[cur].child[0] != -1){
            cur = node[cur].child[0];
        }else{
            ans |= MASK(i);
            cur = node[cur].child[1];
        }
    }
    return ans;
}

/*
    like the same getmin, but priority bit 1 -> save bit 1 |= MASK(i);
    else go bit 0
*/
int getmax(){
    int cur = 0;
    int ans = 0;
    for(int i=30;i>=0;i--){
        if(node[cur].child[1] != -1){
            ans |= MASK(i);
            cur = node[cur].child[1];
        }else{
            cur = node[cur].child[0];
        }
    }
    return ans;
}

/*
    min -> go 0 -> if exist
    +set cnt in that pos -> >= k -> go bit 0
    +if cnt < k -> if nxt exits -= cnt and take bit 1
    
*/

int getmin_kth(int k){
    int cur = 0;
    int ans = 0;
    for(int i=30;i>=0;i--){
        int b = 0;
        int nxt = node[cur].child[b];
        int cnt_b = 0;
        if(nxt != -1){
            cnt_b = node[nxt].cnt;
        }
        if(cnt_b >= k){
            cur = nxt;
        }else{
            if(nxt != -1){
                k -= cnt_b;
            }
            ans |= MASK(i);
            cur = node[cur].child[b ^ 1];
        }
        
    }
    return ans;
}


/*
    like the same getmin_kth -> but go bit 1
*/
int getmax_kth(int k){
    int cur = root;
    int ans = 0;
    for(int i=3;i>=0;i--){
        int b = 1; //go bit 1
        int nxt = node[cur].child[b];
        int cnt_bit = 0;
        if(nxt != -1){
            cnt_bit = node[nxt].cnt;
        }
        if(cnt_bit >= k){
            cur = nxt; //continue go bit 1
            ans |= MASK(i); //take bit 1 in that pos
        }else{
            if(nxt != -1){
                k -= cnt_bit;
            }
            cur  = node[cur].child[b ^ 1]; //else go bit 0

        }
    }
    return ans;
}


int xor_mask = 0;
int getmin_kth_xor(int k){
    int ans = 0;
    int cur = 0;
    for(int i=3;i>=0;i--){
        int b = bit(xor_mask,i);
        //int want = b ^ 1;
        int nxt = node[cur].child[b];
        int cnt_bit = 0;
        if(nxt != -1){
            cnt_bit = node[nxt].cnt;
        }
        if(cnt_bit >= k){
            cur = nxt;
        }else{
            if(nxt != -1){
                k -= cnt_bit;
            }
            ans |= MASK(i);
            cur = node[cur].child[b ^ 1];
        }
    }
    return ans;
}

/*
*/
int getmax_kth_xor(int k){
    int ans = 0;
    int cur = 0;
    for(int i=3;i>=0;i--){
        int b = bit(xor_mask,i);
        int want = b ^ 1;
        int nxt = node[cur].child[want];
        int cnt_bit = 0;
        if(nxt != -1){
            cnt_bit = node[nxt].cnt;
        }
        if(cnt_bit >= k){
            cur = nxt;
            ans |= MASK(i);
        }else{
            if(nxt != -1){
                k -= cnt_bit;
            }
            cur = node[cur].child[want ^ 1];
        }
    }
    return ans;
}

//dfs
void dfs(int cur,int val,int depth){
    if(node[cur].child[0] == -1 && node[cur].child[1] == -1){
        return;
    }
    for(int i=0;i<=1;i++){
        int nxt = node[cur].child[i];
        if(nxt != -1){
            dfs(nxt,(val << 1) | i,depth - 1 );
        }
    }
}

