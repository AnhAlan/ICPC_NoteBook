using T = long double;
const T EPS = 1e-12L;
const T PI  = acosl(-1.0L);
// x in [-EPS, EPS] -> 0, x > EPS -> 1, x < -EPS -> -1
int sgn(T x) { return (x > EPS) - (x < -EPS); }
struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator * (T k) const { return Point(x * k, y * k); }
    Point operator / (T k) const { return Point(x / k, y / k); }
    
    bool operator == (const Point &o) const { return sgn(x - o.x) == 0 && sgn(y - o.y) == 0; }
    bool operator < (const Point &o) const {
        if (sgn(x - o.x) != 0) return sgn(x - o.x) < 0;
        return sgn(y - o.y) < 0;
    }

    T dot(const Point &o) const { return x * o.x + y * o.y; }
    T cross(const Point &o) const { return x * o.y - y * o.x; }
    T cross(const Point &a, const Point &b) const { return (a - *this).cross(b - *this); }

    T len2() const { return x * x + y * y; }
    T len()  const { return sqrtl(len2()); }

    T dist2(const Point &o) const { return (*this - o).len2(); }
    T dist(const Point &o)  const { return (*this - o).len(); }

    Point unit() const { return *this / len(); } // make dist() = 1
    Point perp() const { return Point(-y, x); }  // rotate +90 deg ccw 
    Point normal() const { return perp().unit(); } // perp + unit

    /*
        return radian [-pi, pi]
        degree = radin * (180.0 / PI)
    */
    T angle() const { return atan2l(y, x); } // deg(Ox, (x,y))
    static T angle(const Point &a, const Point &b) { return atan2l(a.cross(b), a.dot(b)); } 

    // rotate this point -> rad
    Point rotate(T rad) const {
        T c = cosl(rad), s = sinl(rad);
        return Point(x * c - y * s, x * s + y * c);
    }
    Point rotate(const Point &o, T rad) const { return (*this - o).rotate(rad) + o; }

    static T orientation(const Point &a, const Point &b, const Point &c) {
        return (b - a).cross(c - a);
    }
    
    static bool on_segment(const Point &a, const Point &b, const Point &c) {
        if (sgn(orientation(a, b, c)) != 0) return false;
        return sgn(c.x - min(a.x, b.x)) >= 0 && sgn(c.x - max(a.x, b.x)) <= 0 &&
               sgn(c.y - min(a.y, b.y)) >= 0 && sgn(c.y - max(a.y, b.y)) <= 0;
    }

    static bool ccw_cmp(const Point &a, const Point &b, const Point &center = Point(0, 0)) {
        Point A = a - center;
        Point B = b - center;
        auto upper = [](const Point &p) {
            return p.y > 0 || (sgn(p.y) == 0 && sgn(p.x) >= 0); 
        };
        bool ua = upper(A);
        bool ub = upper(B);
        if (ua != ub) return ua > ub;
        T cr = A.cross(B);
        if (sgn(cr) != 0) return cr > 0;
        return A.len2() < B.len2();
    }
    /*
        find the center 'c' = total (x,y) / p.size
        sorted CCW around c
        sort(poly.begin(), poly.end(), [&](const Point &a, const Point &b) {
            return Point::ccw_cmp(a, b, c);
            // !Point -> sorted CW
        });
    */
    friend ostream& operator<<(ostream& os, const Point& p) {
        T x = sgn(p.x) == 0 ? 0.0L : p.x;
        T y = sgn(p.y) == 0 ? 0.0L : p.y;
        return os << "(" << x << ", " << y << ")";
    }
};