/**
 * Description: 用法同 set, 只多两个操作:
 * s.order\_of\_key(x): 严格小于 x 的元素个数 (x 不必在集合里);
 * s.find\_by\_order(k): 第 k 小的迭代器, k 从 0 开始.
 * Usage: ordered_set s;
 * s.insert(5); s.insert(1); s.insert(9);
 * int r = s.order_of_key(5); // 1
 * int v = *s.find_by_order(2); // 9
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update>ordered_set;
