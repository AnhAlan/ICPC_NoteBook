#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y));
}

// Brute force for small n
double bruteForce(vector<Point>& P, int l, int r) {
    double ans = 1e18;
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            ans = min(ans, dist(P[i], P[j]));
        }
    }
    return ans;
}

// Divide and conquer main function
double closestUtil(vector<Point>& Px, vector<Point>& Py, int l, int r) {
    int n = r - l + 1;
    if (n <= 3) return bruteForce(Px, l, r);

    int mid = (l + r) / 2;
    double midx = Px[mid].x;

    // Split Py into left/right
    vector<Point> Pyl, Pyr;
    for (auto& p : Py) {
        if (p.x <= midx) Pyl.push_back(p);
        else Pyr.push_back(p);
    }

    double dl = closestUtil(Px, Pyl, l, mid);
    double dr = closestUtil(Px, Pyr, mid + 1, r);
    double d = min(dl, dr);

    // make strip
    vector<Point> strip;
    for (auto& p : Py) {
        if (fabs(p.x - midx) < d) strip.push_back(p);
    }

    // Check in strip
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i + 1; j < (int)strip.size() && j <= i + 7; j++) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    return d;
}

double closestPair(vector<Point>& P) {
    int n = P.size();
    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), [](Point a, Point b) { return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](Point a, Point b) { return a.y < b.y; });
    return closestUtil(Px, Py, 0, n - 1);
}

int main() {
    int n;
    cin >> n;
    vector<Point> P(n);
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;

    cout << fixed << setprecision(6) << closestPair(P) << "\n";
    return 0;
}
