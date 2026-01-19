#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

/* =========================
   ORDERED SET (KHÔNG TRÙNG)
   ========================= */

// ordered_set: set có thứ tự + thống kê
template<class T>
using ordered_set = tree<
    T,                                  // key type
    null_type,                          // mapped type (set)
    less<T>,                            // so sánh
    rb_tree_tag,                        // red-black tree
    tree_order_statistics_node_update   // hỗ trợ order
>;

// ordered_set<int> os;
//
// os.insert(x)         -> chèn x (nếu đã tồn tại thì bỏ qua)
// os.erase(x)          -> xóa x
// os.count(x)          -> 0/1, kiểm tra x có tồn tại
// os.find(x)           -> iterator tới x hoặc end()
//
// os.order_of_key(x)   -> số phần tử < x
// os.find_by_order(k)  -> iterator phần tử đứng thứ k (0-index)
//
// *os.begin()          -> phần tử nhỏ nhất
// *os.rbegin()         -> phần tử lớn nhất
// os.size()            -> số phần tử


/* ============================
   ORDERED MULTISET (CÓ TRÙNG)
   ============================ */

// ordered_multiset: multiset có thứ tự + thống kê
// dùng pair<value, id> để phân biệt các phần tử trùng
template<class T>
using ordered_multiset = tree<
    pair<T,int>,                        // {value, unique_id}
    null_type,
    less<pair<T,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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


/* ============================
   GHI NHỚ NHANH (CHEAT)
   ============================ */

// order_of_key  -> "có bao nhiêu thằng < x?"
// find_by_order -> "thằng đứng thứ k là ai?"
//
// ordered_set       -> không trùng
// ordered_multiset  -> cho trùng (erase bằng iterator)
