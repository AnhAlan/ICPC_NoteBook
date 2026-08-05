struct Big_int {
    static const int base = 1e9;
    vector<int> a;  
    int sign = 1;  
    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }
    static int abs_cmp(const Big_int &x, const Big_int &y) {
        if (x.a.size() != y.a.size())
            return x.a.size() < y.a.size() ? -1 : 1;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            if (x.a[i] != y.a[i])
                return x.a[i] < y.a[i] ? -1 : 1;
        }
        return 0;
    }
    static Big_int abs_add(const Big_int &x, const Big_int &y) {
        Big_int res;
        long long carry = 0;
        for (size_t i = 0; i < max(x.a.size(), y.a.size()) || carry; i++) {
            long long cur = carry;
            if (i < x.a.size()) cur += x.a[i];
            if (i < y.a.size()) cur += y.a[i];
            res.a.push_back(cur % base);
            carry = cur / base;
        }
        return res;
    }
    static Big_int abs_sub(const Big_int &x, const Big_int &y) {
        Big_int res = x;
        long long carry = 0;
        for (size_t i = 0; i < y.a.size() || carry; i++) {
            long long cur = res.a[i] - carry - (i < y.a.size() ? y.a[i] : 0);
            carry = 0;
            if (cur < 0) {
                cur += base;
                carry = 1;
            }
            res.a[i] = cur;
        }
        res.trim();
        return res;
    }

    Big_int(__int128 v = 0) { *this = v; }
    Big_int& operator=(__int128 v) {
        a.clear(); sign = 1;
        if (v < 0) { sign = -1; v = -v; }
        if (v == 0) return *this;
        while (v > 0) {
            a.push_back((int)(v % base));
            v /= base;
        }
        return *this;
    }
    void read(const string &s) {
        a.clear(); sign = 1;
        int i = 0;
        if (s.empty()) return;
        if (s[i] == '-') { sign = -1; i++; }
        for (int j = (int)s.size(); j > i; j -= 9) {
            int l = max(i, j - 9);
            long long x = 0;
            for (int k = l; k < j; k++)
                x = x * 10 + (s[k] - '0');
            a.push_back((int)x);
        }
        trim();
    }
    friend ostream& operator<<(ostream &os, const Big_int &v) {
        if (v.a.empty()) return os << 0;
        if (v.sign == -1) os << '-';
        os << v.a.back();
        for (int i = (int)v.a.size() - 2; i >= 0; i--)
            os << setw(9) << setfill('0') << v.a[i];
        return os;
    }
    friend istream& operator>>(istream &is, Big_int &v) {
        string s; if (is >> s) v.read(s);
        return is;
    }

    friend bool operator< (const Big_int &a, const Big_int &b) {
        if (a.sign != b.sign) return a.sign < b.sign;
        int cmp = abs_cmp(a, b);
        return a.sign == 1 ? cmp < 0 : cmp > 0;
    }
    friend bool operator> (const Big_int &a, const Big_int &b) { return b < a; }
    friend bool operator<=(const Big_int &a, const Big_int &b) { return ! (b < a); }
    friend bool operator>=(const Big_int &a, const Big_int &b) { return ! (a < b); }
    friend bool operator==(const Big_int &a, const Big_int &b) { return a.sign == b.sign && a.a == b.a; }
    friend bool operator!=(const Big_int &a, const Big_int &b) { return ! (a == b); }

    Big_int operator+(const Big_int &v) const {
        Big_int res;
        if (sign == v.sign) {
            res = abs_add(*this, v); res.sign = sign;
        } else {
            if (abs_cmp(*this, v) >= 0) {
                res = abs_sub(*this, v); res.sign = sign;
            } else {
                res = abs_sub(v, *this); res.sign = v.sign;
            }
        }
        res.trim(); return res;
    }

    Big_int operator-(const Big_int &v) const {
        Big_int nv = v; nv.sign *= -1;
        return *this + nv;
    }

    Big_int operator*(const Big_int &v) const {
        Big_int res;
        res.sign = sign * v.sign;
        res.a.assign(a.size() + v.a.size(), 0);
        for (size_t i = 0; i < a.size(); i++) {
            long long carry = 0;
            for (size_t j = 0; j < v.a.size() || carry; j++) {
                long long cur = res.a[i + j] + carry;
                if (j < v.a.size()) cur += 1LL * a[i] * v.a[j];
                res.a[i + j] = cur % base;
                carry = cur / base;
            }
        }
        res.trim(); return res;
    }
};