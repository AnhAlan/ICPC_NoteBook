#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using pbdsm = tree<
    pair<T,int>,
    null_type,
    less<pair<T,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

/*
   pbdsm<int> ms;
   int id = 0;
   ms.insert({x, id++});
   ms.erase(ms.lower_bound({x, 0}));
   ms.order_of_key({x, 0});
   auto it = ms.find_by_order(k);
*/