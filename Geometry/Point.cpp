struct Point {
    static const long double EPS = 1e-12;
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {}

    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator * (long double k) const { return Point(x * k, y * k); }
    Point operator / (long double k) const { return Point(x / k, y / k); }

    long double dot(const Point &o) const { return x * o.x + y * o.y; }
    long double cross(const Point &o) const { return x * o.y - y * o.x; }
    long double cross(const Point &b, const Point &c) const { return (b - *this).cross(c - *this); }

    long double len() const { return sqrt(x*x + y*y); }
    long double len2() const { return x*x + y*y; }

    long double dist(const Point &o) const { return (*this - o).len(); }
    long double dist2(const Point &o) const { return (*this - o).len2(); }

    Point rotate(long double rad) const {
        long double cosA = cos(rad), sinA = sin(rad);
        return Point(x*cosA - y*sinA, x*sinA + y*cosA);
    }
    Point rotate(const Point &o, long double rad) const {
        return (*this - o).rotate(rad) + o;
    }

    bool operator < (const Point &o) const {
        if (fabs(x - o.x) > EPS) return x < o.x;
        return y < o.y;
    }
    bool operator == (const Point &o) const {
        return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
    }

    static long double orientation(const Point &a, const Point &b, const Point &c) {
        return (b - a).cross(c - a);
    }
    static bool onSegment(const Point &a, const Point &b, const Point &c) {
        if (fabs(orientation(a, b, c)) > EPS) return false;
        return c.x >= min(a.x, b.x) - EPS && c.x <= max(a.x, b.x) + EPS
            && c.y >= min(a.y, b.y) - EPS && c.y <= max(a.y, b.y) + EPS;
    }
};