struct AhoCorasick {
    static const int apl = 26;
    struct Trienode {
        Trienode* child[apl];
        Trienode* fail;
        Trienode* nxt[apl];
        vector<int> found;
        Trienode() {
            for(int i = 0; i < apl; i++){
                child[i] = nullptr;
                nxt[i] = nullptr;
            }
            fail = nullptr;
        }
    };
    vector<Trienode> node;
    int cnt;
    Trienode* root;
    AhoCorasick(int maxNodes) {
        node.resize(maxNodes);
        cnt = 0;
        root = create();
    }
    Trienode* create() {
        return &node[cnt++];
    }
    void add_string(const string &s, int id) {
        Trienode* cur = root;
        for (char c : s) {
            int x = c - 'a';
            if (!cur->child[x]) {
                cur->child[x] = create();
            }
            cur = cur->child[x];
        }
        cur->found.push_back(id);
    }
    void build_aho() {
        queue<Trienode*> q;
        root->fail = root;
        for (int i = 0; i < apl; i++) {
            if (root->child[i]) {
                root->child[i]->fail = root;
                root->nxt[i] = root->child[i];
                q.push(root->child[i]);
            } else {
                root->nxt[i] = root;
            }
        }
        while (!q.empty()) {
            Trienode* u = q.front();
            q.pop();
            for (int i = 0; i < apl; i++) {
                Trienode* v = u->child[i];
                if (v) {
                    v->fail = u->fail->nxt[i];
                    for (int id : v->fail->found) {
                        v->found.push_back(id);
                    }
                    q.push(v);
                    u->nxt[i] = v;
                } else {
                    u->nxt[i] = u->fail->nxt[i];
                }
            }
        }
    }
    vector<int> find(const string &s) {
        Trienode* cur = root;
        vector<int> ans;
        for (int i = 0; i < (int)s.size(); i++) {
            cur = cur->nxt[s[i] - 'a'];
            for (int id : cur->found) {
                ans.push_back(id);
                // match[id].push_back(i) -> pattern id ends at position i
            }
        }
        return ans;
    }
};