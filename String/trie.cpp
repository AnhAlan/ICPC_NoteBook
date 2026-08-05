static const int apl = 26;
struct Trie_node{
    Trie_node *child[apl];
    Trie_node(){
        fill(child, child + apl, nullptr);
    }
};
struct Trie{
    vector<Trie_node> node;
    int cnt_node;
    Trie_node *root;
    Trie(int max_node){
        node.resize(max_node);
        cnt_node = 0;
        root = create();
    }
    Trie_node* create(){
        return &node[cnt_node++];
    }
    void add(const string &s){
        Trie_node *cur = root;
        for(char c : s){
            int id = c - 'a';
            if(!cur->child[id]){
                cur->child[id] = create();
            }
            cur = cur->child[id];
        }
    }
};