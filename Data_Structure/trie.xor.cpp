#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct trienode {
        int child[2];
        int cnt;
        trienode() {
            child[0] = child[1] = -1;
            cnt = 0;
        }
    };
    vector<trienode> node;
    int root;
    int cnt_node;
    int xor_mask;
    Trie(int max_nodes = 2e6) {
        node.resize(max_nodes);
        root = 0;
        cnt_node = 1;
        xor_mask = 0;
    }
    int create() {
        return cnt_node++;
    }
    //add binary
    void add(int k) {
        int cur = root;
        node[cur].cnt++;
        for(int i = 30; i >= 0; i--) {
            int b = ((k >> i) & 1);
            if(node[cur].child[b] == -1) {
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
            ans |= (1ll << i)
    */
    int get_min() {
        int cur = root;
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            if(node[cur].child[0] != -1) {
                cur = node[cur].child[0];
            } else {
                ans |= (1ll << i);
                cur = node[cur].child[1];
            }
        }
        return ans;
    }
    /*
        like the same getmin, but priority bit 1 -> save bit 1 |= (1ll << i);
        else go bit 0
    */
    int get_max() {
        int cur = root;
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            if(node[cur].child[1] != -1) {
                ans |= (1ll << i); 
                cur = node[cur].child[1];
            } else {
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
    int getmin_kth(int k) {
        int cur = root; 
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            int b = 0;
            int nxt = node[cur].child[b];
            int cnt_b = 0;
            if(nxt != -1) {
                cnt_b = node[nxt].cnt;
            }
            if(cnt_b >= k) {
                cur = nxt;
            } else {
                if(nxt != -1) {
                    k -= cnt_b;
                }
                ans |= (1ll << i); 
                cur = node[cur].child[b ^ 1];
            }
        }
        return ans;
    }
    /*
        like the same getmin_kth -> but go bit 1
    */
    int getmax_kth(int k) {
        int cur = root;
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            int b = 1; //go bit 1
            int nxt = node[cur].child[b];
            int cnt_bit = 0;
            if(nxt != -1) {
                cnt_bit = node[nxt].cnt;
            }
            if(cnt_bit >= k) {
                cur = nxt; //continue go bit 1
                ans |= (1ll << i); //take bit 1 in that pos // Đã sửa lỗi: < thành <<
            } else {
                if(nxt != -1) {
                    k -= cnt_bit;
                }
                cur  = node[cur].child[b ^ 1]; //else go bit 0
            }
        }
        return ans;
    }
    int getmin_kth_xor(int k) {
        int ans = 0;
        int cur = root; 
        for(int i = 30; i >= 0; i--) {
            int b = ((xor_mask >> i) & 1); 
            int nxt = node[cur].child[b];
            int cnt_bit = 0;
            if(nxt != -1) {
                cnt_bit = node[nxt].cnt;
            }
            if(cnt_bit >= k) {
                cur = nxt;
            } else {
                if(nxt != -1) {
                    k -= cnt_bit;
                }
                ans |= (1ll << i);
                cur = node[cur].child[b ^ 1];
            }
        }
        return ans;
    }
    int getmax_kth_xor(int k) {
        int ans = 0;
        int cur = root;
        for(int i = 30; i >= 0; i--) {
            int b = ((xor_mask >> i) & 1);
            int want = b ^ 1;
            int nxt = node[cur].child[want];
            int cnt_bit = 0;
            if(nxt != -1) {
                cnt_bit = node[nxt].cnt;
            }
            if(cnt_bit >= k) {
                cur = nxt;
                ans |= (1ll << i);
            } else {
                if(nxt != -1) {
                    k -= cnt_bit;
                }
                cur = node[cur].child[want ^ 1];
            }
        }
        return ans;
    }
    void dfs(int cur, int val, int depth) {
        if(node[cur].child[0] == -1 && node[cur].child[1] == -1) {
            return;
        }
        for(int i = 0; i <= 1; i++) {
            int nxt = node[cur].child[i];
            if(nxt != -1) {
                dfs(nxt, (val << 1) | i, depth - 1);
            }
        }
    }
};