/**
 * Description: pb\_ds 平衡树 ordered\_set: 有序集合, 比 set 多两个操作,
 * 求排名 order\_of\_key 和求第 k 小 find\_by\_order, 都是 $O(\log n)$.
 * 元素互不相同, 重复插入无效. 其余接口同 set: insert, erase, find,
 * lower\_bound, upper\_bound, size, clear, begin, end.
 * s.order\_of\_key(x): 返回严格小于 x 的元素个数, x 不必在集合里.
 * s.find\_by\_order(k): 返回第 k 小的迭代器, k 从 0 开始, k 不小于 size 时为 end.
 * 换元素类型: 改 typedef 里的两个 int, 例如换成 ll. 当 map 用: 把 null\_type 换成值类型.
 * 要可重: 元素换成 pair, first 存值, second 存互不相同的编号, 如插入时间,
 * 此时 x 的排名为 order\_of\_key(\{x, 0\}), 要求编号都大于 0.
 * 注意: 需要 GCC; 常数比 set 大约 2 到 3 倍.
 * Usage: ordered_set s; // 多组数据: s.clear();
 * s.insert(5); s.insert(1); s.insert(9);
 * int r = s.order_of_key(5); // 1, 严格小于 5 的有 1 个
 * int v = *s.find_by_order(2); // 9, 即第 2 小, 从 0 开始数
 * if (s.find(1) != s.end()) s.erase(1);
 * // 值在 [3, 10) 内的个数:
 * int cnt = s.order_of_key(10) - s.order_of_key(3);
 * Time: 每次操作 O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update>ordered_set;
