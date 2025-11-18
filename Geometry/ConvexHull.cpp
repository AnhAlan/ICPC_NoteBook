/*
    lower hull:
        + if cross <= 0 → turn is right or collinear → remove the middle point
        + if cross > 0  → left turn → keep the point

    upper hull:
        + same logic as lower (cross <= 0 → remove)

    finally:
        + resize to remove the duplicated start/end point
*/


double cross(const Point &a, const Point &b, const Point &c) {
    return (b - a).cross(c - a);
}

vector<Point> convexHull(vector<Point> v) {
    int n = v.size();
    if (n <= 2) return v;

    sort(v.begin(), v.end());

    vector<Point> ch(2 * n);
    int sz = 0;

    // Lower hull
    for (int i = 0; i < n; i++) {
        while (sz > 1 && cross(ch[sz-2], ch[sz-1], v[i]) <= 0) sz--;
        ch[sz++] = v[i];
    }

    // Upper hull
    for (int i = n - 2, up = sz; i >= 0; i--) {
        while (sz > up && cross(ch[sz-2], ch[sz-1], v[i]) <= 0) sz--;
        ch[sz++] = v[i];
    }


    ch.resize(sz - 1);
    return ch;
}

