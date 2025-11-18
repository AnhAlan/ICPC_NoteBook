/*
    point a(3,4);
    point b(1,2);
    point c = a + b;
    double t = c.corss(b)
    double area = a.cross(b)
    sort(a.begin(),a.end()) // if have a vector point
*/

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Add and subtract vectors
    Point operator + (const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point &o) const { return Point(x - o.x, y - o.y); }
    
    // Multiply / divide by numbers
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }

    // Dot & Cross
    double dot(const Point &o) const { return x * o.x + y * o.y; }
    double cross(const Point &o) const { return x * o.y - y * o.x; }

    // length
    double len() const { return sqrt(x * x + y * y); }

    // Compare (used for sort)
    bool operator < (const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Point &o) const {
        return fabs(x - o.x) < 1e-9 && fabs(y - o.y) < 1e-9;
    }
};
