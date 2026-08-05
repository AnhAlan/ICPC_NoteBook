static const int apl = 26;
struct Trie_node{
    Trie_node *child[apl];
    Trie_node *nxt[apl];
    Trie_node *fail;
    vector<int> found;
    Trie_node(){
        for (int i = 0; i < apl; i++) {
            child[i] = nxt[i] = nullptr;
        }
        fail = nullptr;
    }
};
struct Aho_corasick{
    vector<Trie_node> nodes;
    Trie_node *root;
    int cnt_node;
    Aho_corasick(int max_node){
        nodes.resize(max_node);
        cnt_node = 0;
        root = create();
    }
    Trie_node *create(){
        return &nodes[cnt_node++];
    }
    void add(const string &s, int id){
        Trie_node *cur = root;
        for (const char &c : s){
            if (cur->child[c - 'a'] == nullptr){
                cur->child[c - 'a'] = create();
            }
            cur = cur->child[c - 'a'];
        }
        cur->found.push_back(id);
    }
    void build(){
        root->fail = root;
        queue<Trie_node*> q;
        for (int i = 0; i < apl; i++){
            if (root->child[i] != nullptr){
                Trie_node *u = root->child[i];
                root->nxt[i] = u;
                root->nxt[i]->fail = root;
                for (int j = 0; j < apl; j++){
                    u->nxt[j] = (u->child[j] != nullptr ? u->child[j] : u->fail->nxt[j]);
                }
                q.push(u);
            }else {
                root->nxt[i] = root;
            }
        }

        while (!q.empty()){
            Trie_node *u = q.front();
            q.pop();
            for (int id : u->fail->found){
                u->found.push_back(id);
            }
            for (int i = 0; i < apl; i++){
                if (u->child[i] == nullptr) continue;
                Trie_node *v = u->child[i];
                v->fail = u->fail->nxt[i];
                for (int j = 0; j < apl; j++){
                    v->nxt[j] = (v->child[j] != nullptr ? v->child[j] : v->fail->nxt[j]);
                }
                q.push(v);
            }
        }
    }
};