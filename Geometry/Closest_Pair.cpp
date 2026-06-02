long double bruteForce(vector<Point> &P, int l, int r) {
    long double ans = 1e18;
    for (int i = l; i <= r; i++) {
        for (int j = i+1; j <= r; j++) {
            ans = min(ans, P[i].dist(P[j]));
        }
    }
    return ans;
}
long double closestUtil(vector<Point> &Px, vector<Point> &Py, int l, int r) {
    int n = r - l + 1;
    if (n <= 3) return bruteForce(Px, l, r);
    int mid = (l + r) / 2;
    long double midx = Px[mid].x;
    vector<Point> Pyl, Pyr;
    for (auto &p : Py) {
        if (p.x <= midx) Pyl.push_back(p);
        else Pyr.push_back(p);
    }
    long double dl = closestUtil(Px, Pyl, l, mid);
    long double dr = closestUtil(Px, Pyr, mid+1, r);
    long double d = min(dl, dr);
    vector<Point> strip;
    for (auto &p : Py) {
        if (fabs(p.x - midx) < d) strip.push_back(p);
    }
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i+1; j < (int)strip.size() && j <= i+7; j++) {
            d = min(d, strip[i].dist(strip[j]));
        }
    }
    return d;
}
long double closestPair(const vector<Point> &P) {
    int n = P.size();
    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), [](const Point &a, const Point &b){ return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const Point &a, const Point &b){ return a.y < b.y; });
    return closestUtil(Px, Py, 0, n-1);
}