const int mod = (int) 1e9 + 7;
template<typename T>
void add(T &x, const T &y){
    x += y;
    if (x < 0) x += mod;
    if (x >= mod) x -= mod;
}
