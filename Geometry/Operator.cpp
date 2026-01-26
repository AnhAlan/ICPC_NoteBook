
const long double PI = acosl(-1.0L);
const double EPS = 1e-9;

struct Point {
    double x, y;

    // Constructor
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Vector addition / subtraction
    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }

    // Multiply / divide by scalar
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }

    // Dot product
    double dot(const Point &o) const { return x * o.x + y * o.y; }

    // Cross product (2D)
    double cross(const Point &o) const { return x * o.y - y * o.x; }

    // 2D Cross product with three points: AB x AC
    double cross(const Point &b, const Point &c) const {
        return (b - *this).cross(c - *this);
    }

    // Length (magnitude)
    double len() const { return sqrt(x*x + y*y); }

    // Squared length (to avoid sqrt)
    double len2() const { return x*x + y*y; }

    // Distance to another point
    double dist(const Point &o) const { return (*this - o).len(); }

    // Squared distance
    double dist2(const Point &o) const { return (*this - o).len2(); }

    // Rotate point around origin by angle rad (counter-clockwise)
    Point rotate(double rad) const {
        double cosA = cos(rad), sinA = sin(rad);
        return Point(x*cosA - y*sinA, x*sinA + y*cosA);
    }

    // Rotate point around another point
    Point rotate(const Point &o, double rad) const {
        return (*this - o).rotate(rad) + o;
    }

    // Comparison operators for sorting
    bool operator < (const Point &o) const {
        if (fabs(x - o.x) > EPS) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Point &o) const {
        return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
    }
};

// Global reference point for polar sort
Point p0;

// Polar angle comparison (CCW)
bool polar_cmp(const Point &a, const Point &b) {
    double angA = atan2(a.y - p0.y, a.x - p0.x);
    double angB = atan2(b.y - p0.y, b.x - p0.x);
    if (fabs(angA - angB) > EPS) return angA < angB; // CCW
    return a.dist2(p0) < b.dist2(p0); // closer first if same angle
}

// Check orientation of three points
// >0: counter-clockwise, <0: clockwise, 0: collinear
double orientation(const Point &a, const Point &b, const Point &c) {
    return (b - a).cross(c - a);
}

// Check if point c is on segment ab
bool onSegment(const Point &a, const Point &b, const Point &c) {
    if (fabs(orientation(a, b, c)) > EPS) return false;
    return c.x >= min(a.x, b.x) - EPS && c.x <= max(a.x, b.x) + EPS
        && c.y >= min(a.y, b.y) - EPS && c.y <= max(a.y, b.y) + EPS;
}

// Angle between two vectors
double angle(const Point &a, const Point &b) {
    double cosA = a.dot(b) / (a.len() * b.len());
    return acos(max(-1.0, min(1.0, cosA))); // clamp for precision
}
    /*
    Point a(3,4), b(1,2);
    Point c = a + b;
    double area = a.cross(b); // area of parallelogram
    double orient = orientation(a,b,c); // ccw, cw, collinear
    vector<Point> v = {a,b,c};
    sort(v.begin(),v.end()); // sort by x, then y
    */

