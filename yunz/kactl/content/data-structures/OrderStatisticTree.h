/**
 * Description: pb\_ds 平衡树, 不可重集合, 不是 multiset. 支持求排名和第 k 小.
 * 当 map 用: 把 null\_type 换成值类型. 换元素类型只改 typedef 里的两个 int.
 * 要可重: 元素换成 pair, first 存值, second 存互不相同的编号.
 * Usage: ordered_set s; s.insert(x); s.erase(x);
 * int r = s.order_of_key(x); // 严格小于 x 的个数
 * int v = *s.find_by_order(k); // 第 k 小, k 从 0 开始
 * // k 不小于 s.size() 时返回 s.end()
 * s.lower_bound(x); s.size(); s.clear(); // 同 set
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update>ordered_set;
