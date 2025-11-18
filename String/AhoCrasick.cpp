#include <bits/stdc++.h>
using namespace std;

const int apl = 26;
const int maxn = 1e3;

struct trienode{
    trienode* child[apl];
    trienode* fail;
    trienode* next[apl];
    vector<int>found;
    trienode(){
        for(int i=0;i<apl;i++){
            child[i] = next[i] = nullptr; 
        }
        fail = nullptr;
    }
};

trienode node[maxn];
int cntnode = 0;

trienode* create(){
    return &node[cntnode++];
}

trienode* root = create();

void add(string words,int id){
    trienode* cur = root;
    for(char c : words){
        if(!cur->child[c-'a']){
            cur->child[c-'a'] = create();
        }
        cur = cur->child[c-'a'];
    }
    cur->found.push_back(id);
}

void ac_bfs(){
    root->fail = root;
    queue<trienode*> q;

    for(int i=0;i<26;i++){
        if(root->child[i]){
            root->child[i]->fail = root;
            root->next[i] = root->child[i];
            q.push(root->child[i]);
        }else{
            root->next[i] = root;
        }
    }

    while(!q.empty()){
        trienode* u = q.front();
        q.pop();
        for(int i=0;i<26;i++){
            trienode* v = u->child[i];
            if(v){
                v->fail = u->fail->next[i];
                for(int id : v->fail->found){
                    v->found.push_back(id);
                }
                q.push(v);
            }
            u->next[i] = v ? v : u->fail->next[i];
        }
    }
}


void process(string tmp){
    trienode* cur = root;
    for(int i=0;i<(int)tmp.size();i++){
        cur = cur->next[tmp[i]-'a'];
        if(!cur->found.empty()){
            cout << "match at " << i+1 << ": ";
            for(int id : cur->found){
                cout << id << " ";
            }
            cout << "\n";
        }
    }
}

void solve(){
    int n;
    cin >> n;

    vector<string>words(n);
    for(int i=0;i<n;i++){
        cin >> words[i];
        add(words[i],i+1);
    }
    ac_bfs();
    string t;
    cin >> t;
    process(t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
