template<class X, class Y>
bool minimize (X &x, const Y &y){ return x > y ? x = y, true : false;}
template<class X, class Y>
bool maximize (X &x, const Y &y){ return x < y ? x = y, true : false;}