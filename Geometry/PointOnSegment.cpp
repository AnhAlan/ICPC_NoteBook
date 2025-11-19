#include <bits/stdc++.h>
using namespace std;

// Function returns integer points on line segment (x1,y1) -> (x2,y2)
vector<pair<int,int>> points_on_segment(int x1,int y1,int x2,int y2){
    vector<pair<int,int>> res;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int g = gcd(abs(dx), abs(dy)); // number of steps between integer points
    int stepX = dx / g;
    int stepY = dy / g;
    for(int i = 0; i <= g; i++){
        int x = x1 + i * stepX;
        int y = y1 + i * stepY;
        res.push_back({x,y});
    }
    return res;
}

int main(){
    int x1=0,y1=0,x2=4,y2=0;
    auto pts = points_on_segment(x1,y1,x2,y2);
    for(auto p: pts) cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";
}
