#include <bits/stdc++.h>
using namespace std;


#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ", dbg(__VA_ARGS__), cerr << "\n"
// Pair
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// Vector 1D
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i];
        if (i + 1 < v.size()) os << ",";
    }
    os << "}";
    return os;
}

// Vector 2D 
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
    os << "{" << "\n";
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v[i].size(); j++) {
            os << v[i][j];
            if (j + 1 < v[i].size()) os << ",";
        }
        os << "\n";
    }
    os << "}";
    return os;
}

// Set
template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    auto it = s.begin();
    while (it != s.end()) {
        os << *it;
        ++it;
        if (it != s.end()) os << ",";
    }
    os << "}";
    return os;
}

// Unordered Set
template<typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& s) {
    os << "{";
    auto it = s.begin();
    while (it != s.end()) {
        os << *it;
        ++it;
        if (it != s.end()) os << ",";
    }
    os << "}";
    return os;
}

// Multiset
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& s) {
    os << "{";
    auto it = s.begin();
    while (it != s.end()) {
        os << *it;
        ++it;
        if (it != s.end()) os << ",";
    }
    os << "}";
    return os;
}

// Map
template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& mp) {
    os << "{\n";
    auto it = mp.begin();
    while (it != mp.end()) {
        os << "  " << it->first << " -> " << it->second << "\n";
        ++it;
    }
    os << "}";
    return os;
}

// Unordered Map
template<typename K, typename V>
ostream& operator<<(ostream& os, const unordered_map<K, V>& mp) {
    os << "{\n";
    auto it = mp.begin();
    while (it != mp.end()) {
        os << "  " << it->first << " -> " << it->second << "\n";
        ++it;
    }
    os << "}";
    return os;
}

// Deque
template<typename T>
ostream& operator<<(ostream& os, const deque<T>& dq) {
    os << "{";
    for (size_t i = 0; i < dq.size(); i++) {
        os << dq[i];
        if (i + 1 < dq.size()) os << ",";
    }
    os << "}";
    return os;
}

// Priority Queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& os, priority_queue<T, Container, Compare> pq) {
    os << "{";
    while (!pq.empty()) {
        os << pq.top();
        pq.pop();
        if (!pq.empty()) os << ",";
    }
    os << "}";
    return os;
}

// Queue
template<typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{";
    while (!q.empty()) {
        os << q.front();
        q.pop();
        if (!q.empty()) os << ",";
    }
    os << "}";
    return os;
}

// Stack
template<typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    vector<T> v;
    while (!st.empty()) {
        v.push_back(st.top());
        st.pop();
    }
    os << "{";
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        os << v[i];
        if (i > 0) os << ",";
    }
    os << "}";
    return os;
}

// debug arr + vector [l, r]
template<typename T>
struct dbg_arr_wrapper {
    const T* arr;
    int l, r;
    friend ostream& operator<<(ostream& os, const dbg_arr_wrapper& w) {
        os << "[";
        for (int i = w.l; i <= w.r; i++) {
            os << w.arr[i];
            if (i < w.r) os << ",";
        }
        os << "]";
        return os;
    }
};
template<typename T>
dbg_arr_wrapper<T> dbg_arr(const T arr[], int l, int r) { return {arr, l, r}; }
template<typename T>
dbg_arr_wrapper<T> dbg_arr(const T arr[], int n) { return {arr, 0, n - 1}; }
template<typename T>
struct dbg_sub_wrapper {
    const vector<T>& v;
    int l, r;
    friend ostream& operator<<(ostream& os, const dbg_sub_wrapper& w) {
        os << "{";
        for (int i = w.l; i <= w.r; i++) {
            if (i >= 0 && i < (int)w.v.size()) {
                os << w.v[i];
                if (i < w.r) os << ",";
            }
        }
        os << "}";
        return os;
    }
};
template<typename T>
dbg_sub_wrapper<T> dbg_sub(const vector<T>& v, int l, int r) { return {v, l, r}; }
#define debug_arr(arr, l, r) debug(dbg_arr(arr, l, r))
#define debug_vec(v, l, r) debug(dbg_sub(v, l, r))

// Bitset
template<size_t N>
ostream& operator<<(ostream& os, const bitset<N>& b) {
    os << b.to_string();
    return os;
}

// main debug
void dbg() {}
template<typename T, typename... Args>
void dbg(const T& a, const Args&... args) {
    cerr << a;
    if (sizeof...(args)) cerr << ", ";
    dbg(args...);
}
