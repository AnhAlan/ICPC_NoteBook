vector<Point> convexHull(const vector<Point> &pts) {
    int n = pts.size();
    if (n <= 2) return pts; 
    sort(pts.begin(), pts.end());
    vector<Point> ch(2 * n);
    int sz = 0;
    // Lower hull
    for (int i = 0; i < n; i++) {
        while (sz > 1 && Point::orientation(ch[sz-2], ch[sz-1], pts[i]) <= 0) sz--;
        ch[sz++] = pts[i];
    }
    // Upper hull
    int t = sz;
    for (int i = n - 2; i >= 0; i--) {
        while (sz > t && Point::orientation(ch[sz-2], ch[sz-1], pts[i]) <= 0) sz--;
        ch[sz++] = pts[i];
    }
    ch.resize(sz - 1); 
    return ch;
}