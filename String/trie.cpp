struct Trie{
    struct TrieNode{
        TrieNode *child[26];
        TrieNode(){
            fill(child, child + 26, nullptr);
        }
    };
    vector<TrieNode> node;
    int cnt_node;
    TrieNode *root;
    Trie(int _maxNode){
        node.resize(_maxNode);
        cnt_node = 0;
        root = create();
    }
    TrieNode* create(){
        return &node[cnt_node++];
    }
    void add(const string &s){
        TrieNode *cur = root;
        for(char c : s){
            int id = c - 'a';
            if(!cur->child[id]){
                cur->child[id] = create();
            }
            cur = cur->child[id];
        }
    }
};