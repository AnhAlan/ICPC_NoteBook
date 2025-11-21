#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n, m;
vector<int> luu[1001];
bool check[1001];
vector<int> poto;
int ban_bac_vao[1001];

void nhap(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int x, y;
        cin >> x >> y;
        luu[x].push_back(y);   // directed edge x -> y
        ban_bac_vao[y]++;      // y has one more incoming edge
    }
    memset(check, false, sizeof(check));
}

void kahn(){
    queue<int> q;

    // Push all nodes with in-degree = 0 into the queue
    for(int i = 1; i <= n; i++){
        if(ban_bac_vao[i] == 0){
            q.push(i);
        }
    }

    // BFS-like process for Kahn's Algorithm
    while(!q.empty()){
        int u = q.front();
        q.pop();

        poto.push_back(u); // add this node to topological order

        // Remove all outgoing edges from u
        for(int x : luu[u]){
            ban_bac_vao[x]--;  // decrease in-degree of neighbor
            if(ban_bac_vao[x] == 0){ // if it becomes 0, add to queue
                q.push(x);
            }
        }
    }

    // If topo order does not contain all nodes => there is a cycle
    if ((int)poto.size() != n) {
        cout << "NO\n"; // cycle detected
    } else {
        for (int x : poto) cout << x << " ";
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    nhap();
    kahn();

    return 0;
}
