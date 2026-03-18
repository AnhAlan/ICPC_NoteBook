struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }

    double dot(const Point &o) const { return x * o.x + y * o.y; }
    double cross(const Point &o) const { return x * o.y - y * o.x; }
    double cross(const Point &b, const Point &c) const { return (b - *this).cross(c - *this); }

    double len() const { return sqrt(x*x + y*y); }
    double len2() const { return x*x + y*y; }

    double dist(const Point &o) const { return (*this - o).len(); }
    double dist2(const Point &o) const { return (*this - o).len2(); }

    Point rotate(double rad) const {
        double cosA = cos(rad), sinA = sin(rad);
        return Point(x*cosA - y*sinA, x*sinA + y*cosA);
    }
    Point rotate(const Point &o, double rad) const {
        return (*this - o).rotate(rad) + o;
    }

    bool operator < (const Point &o) const {
        if (fabs(x - o.x) > EPS) return x < o.x;
        return y < o.y;
    }
    bool operator == (const Point &o) const {
        return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
    }

    static double orientation(const Point &a, const Point &b, const Point &c) {
        return (b - a).cross(c - a);
    }
    static bool onSegment(const Point &a, const Point &b, const Point &c) {
        if (fabs(orientation(a, b, c)) > EPS) return false;
        return c.x >= min(a.x, b.x) - EPS && c.x <= max(a.x, b.x) + EPS
            && c.y >= min(a.y, b.y) - EPS && c.y <= max(a.y, b.y) + EPS;
    }
    static double angle(const Point &a, const Point &b) {
        double cosA = a.dot(b) / (a.len() * b.len());
        return acos(max(-1.0, min(1.0, cosA)));
    }
    static bool polar_cmp(const Point &a, const Point &b, const Point &p0) {
        double angA = atan2(a.y - p0.y, a.x - p0.x);
        double angB = atan2(b.y - p0.y, b.x - p0.x);
        if (fabs(angA - angB) > EPS) return angA < angB; // CCW
        return a.dist2(p0) < b.dist2(p0); 
    }
};