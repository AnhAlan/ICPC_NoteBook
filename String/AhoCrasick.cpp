struct AhoCorasick {
    static const int apl = 26;
    struct Trienode {
        Trienode* child[apl];
        Trienode* nxt[apl];
        Trienode* fail;
        Trienode* link; 
        int id;       
        int cnt;     
        int total_cnt;  
        Trienode() {
            for(int i = 0; i < apl; i++){
                child[i] = nullptr;
                nxt[i] = nullptr;
            }
            fail = nullptr;
            link = nullptr;
            id = -1;
            cnt = 0;
            total_cnt = 0;
        }
    };

    vector<Trienode> node;
    int cnt;
    Trienode* root;
    vector<Trienode*> bfs_order; 
    
    AhoCorasick(int maxNodes) {
        node.resize(maxNodes);
        cnt = 0;
        root = create();
        bfs_order.reserve(maxNodes);
    }
    
    Trienode* create() {
        return &node[cnt++];
    }
    
    void add(const string &s, int pattern_id) {
        Trienode* cur = root;
        for (char c : s) {
            int x = c - 'a';
            if (!cur->child[x]) {
                cur->child[x] = create();
            }
            cur = cur->child[x];
        }
        cur->id = pattern_id; 
        cur->cnt++;        
    }
    
    void build() {
        queue<Trienode*> q;
        root->fail = root;
        root->link = root;
        
        for (int i = 0; i < apl; i++) {
            if (root->child[i]) {
                root->child[i]->fail = root;
                root->child[i]->link = root;
                root->nxt[i] = root->child[i];
                q.push(root->child[i]);
            } else {
                root->nxt[i] = root;
            }
        }
        
        while (!q.empty()) {
            Trienode* u = q.front();
            q.pop();
            bfs_order.push_back(u); 
            u->total_cnt = u->cnt + u->fail->total_cnt;
            for (int i = 0; i < apl; i++) {
                Trienode* v = u->child[i];
                if (v) {
                    v->fail = u->fail->nxt[i];
                    if (v->fail->id != -1) {
                        v->link = v->fail;
                    } else {
                        v->link = v->fail->link;
                    }
                    q.push(v);
                    u->nxt[i] = v;
                } else {
                    u->nxt[i] = u->fail->nxt[i];
                }
            }
        }
    }
    
    long long count_match(const string &s) {
        long long total = 0;
        Trienode* cur = root;
        for (char c : s) {
            cur = cur->nxt[c - 'a'];
            total += cur->total_cnt; 
        }
        return total;
    }

    vector<int> match_id(const string &s, int num_patterns) {
        vector<int> node_visits(cnt, 0);
        Trienode* cur = root;
        for (char c : s) {
            cur = cur->nxt[c - 'a'];
            int idx = cur - &node[0];
            node_visits[idx]++;
        }
        vector<int> res(num_patterns, 0);
        for (int i = (int)bfs_order.size() - 1; i >= 0; i--) {
            Trienode* u = bfs_order[i];
            int u_idx = u - &node[0];
            if (u->id != -1) {
                res[u->id] += node_visits[u_idx];
            }
            int fail_idx = u->fail - &node[0];
            node_visits[fail_idx] += node_visits[u_idx];
        }
        
        return res;
    }
};