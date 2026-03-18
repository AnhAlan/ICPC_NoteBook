using namespace std;
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// ordered_set<int> os;
// ordered_set<int> os;
//
// os.insert(x)         -> inserts x (duplicates ignored)
// os.erase(x)          -> removes x
// os.count(x)          -> returns 0/1, checks if x exists
// os.find(x)           -> iterator to x or end()
//
// os.order_of_key(x)   -> number of elements strictly less than x
// os.find_by_order(k)  -> iterator to k-th element (0-indexed)
//
// *os.begin()          -> smallest element
// *os.rbegin()         -> largest element
// os.size()            -> number of elements
template<class T>
using ordered_set = tree<
    T,                                  // key type
    null_type,                          // mapped type (like value, unused here)
    less<T>,                            // comparator
    rb_tree_tag,                        // red-black tree structure
    tree_order_statistics_node_update   // supports order statistics
>;



/* ============================
   ORDERED MULTISET (CÓ TRÙNG)
   ============================ */

// ordered_multiset: multiset có thứ tự + thống kê
// dùng pair<value, id> để phân biệt các phần tử trùng
// ordered_multiset<int> oms;
// int id = 0;
//
// oms.insert({x, id++})     -> chèn x (cho phép trùng)
// oms.erase(it)             -> xóa phần tử tại iterator it
// oms.size()                -> tổng số phần tử
//
// oms.order_of_key({x, -1})     -> số phần tử < x
// oms.order_of_key({x, INF})    -> số phần tử <= x
//
// oms.find_by_order(k)      -> iterator phần tử thứ k (0-index)
// it->first                 -> giá trị thật (value)
// it->second                -> id phân biệt trùng
//
// *oms.begin()              -> phần tử nhỏ nhất
// *oms.rbegin()             -> phần tử lớn nhất


/* ============================
   XÓA 1 PHẦN TỬ x TRONG OMS
   ============================ */

// auto it = oms.lower_bound({x, -1});
// if(it != oms.end() && it->first == x){
//     oms.erase(it);
// }
template<class T>
using ordered_multiset = tree<
    pair<T,int>,                        // {value, unique_id}
    null_type,
    less<pair<T,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;



/* ============================
   GHI NHỚ NHANH (CHEAT)
   ============================ */

// order_of_key  -> "có bao nhiêu thằng < x?"
// find_by_order -> "thằng đứng thứ k là ai?"
//
// ordered_set       -> không trùng
// ordered_multiset  -> cho trùng (erase bằng iterator)
