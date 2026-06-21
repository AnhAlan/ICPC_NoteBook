const long double EPS = 1e-12L;
const long double PI  = acosl(-1.0L);
// check real number x
int sgn(long double x) {
    if (fabsl(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
bool isClose(long double a, long double b) {
    return fabsl(a - b) < EPS * max({1.0L, fabsl(a), fabsl(b)});
}
struct Point {
    long double x, y;
    Point(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}

    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator * (long double k) const { return Point(x * k, y * k); }
    Point operator / (long double k) const { return Point(x / k, y / k); }

    long double dot(const Point &o) const { return x * o.x + y * o.y; }
    long double cross(const Point &o) const { return x * o.y - y * o.x; }
    long double cross(const Point &a, const Point &b) const {
        return (a - *this).cross(b - *this);
    }

    long double len2() const { return x * x + y * y; }
    long double len()  const { return sqrtl(len2()); }

    long double dist2(const Point &o) const { return (*this - o).len2(); }
    long double dist(const Point &o)  const { return (*this - o).len(); }

    Point rotate(long double rad) const {
        long double c = cosl(rad), s = sinl(rad);
        return Point(x * c - y * s, x * s + y * c);
    }

    Point rotate(const Point &o, long double rad) const {
        return (*this - o).rotate(rad) + o;
    }

    //sorted x increases then y increases
    bool operator < (const Point &o) const {
        if (fabsl(x - o.x) > EPS) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Point &o) const {
        return fabsl(x - o.x) < EPS && fabsl(y - o.y) < EPS;
    }

    //check if x,y >= 1e8
    bool isEqual(const Point &o) const {
        return fabsl(x - o.x) < EPS * max({1.0L, fabsl(x), fabsl(o.x)}) &&
               fabsl(y - o.y) < EPS * max({1.0L, fabsl(y), fabsl(o.y)});
    }

    static long double orientation(const Point &a, const Point &b, const Point &c) {
        return (b - a).cross(c - a);
    }

    static bool onSegment(const Point &a, const Point &b, const Point &c) {
        if (fabsl(orientation(a, b, c)) > EPS) return false;
        return min(a.x, b.x) - EPS <= c.x && c.x <= max(a.x, b.x) + EPS &&
               min(a.y, b.y) - EPS <= c.y && c.y <= max(a.y, b.y) + EPS;
    }

    static long double angle(const Point &a, const Point &b) {
        long double cosA = a.dot(b) / (a.len() * b.len());
        cosA = max((long double)-1.0, min((long double)1.0, cosA));
        return acosl(cosA);
    }

    static bool ccw_cmp(const Point &a, const Point &b, const Point &center) {
        Point A = a - center;
        Point B = b - center;
        auto upper = [](const Point &p) {
            return p.y > 0 || (fabsl(p.y) < EPS && p.x >= 0);
        };
        bool ua = upper(A);
        bool ub = upper(B);
        if (ua != ub) return ua > ub;
        long double cr = A.cross(B);
        if (fabsl(cr) > EPS) return cr > 0;
        return A.len2() < B.len2();
    }
    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
    /*
        find the center 'c' = total (x,y) / p.size
        sorted CCW around c
        sort(poly.begin(), poly.end(), [&](const Point &a, const Point &b) {
            return Point::ccw_cmp(a, b, c);
            // !Point -> sorted CW
        });
    */
};