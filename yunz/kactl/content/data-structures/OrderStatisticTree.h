/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: 不可重集合 (不是 multiset!), 支持求第 n 个元素和求元素的排名.
 * 要当 map 用, 把 \texttt{null\_type} 换成值类型.
 * Usage: Tree<int> t; t.insert(x); int r = t.order_of_key(x);
 * int v = *t.find_by_order(k); // 第 k 小, 从 0 开始
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree=tree<T,null_type,less<T>,rb_tree_tag,
    tree_order_statistics_node_update>;

void example(){
	Tree<int>t,t2;t.insert(8);
	auto it=t.insert(10).first;
	assert(it==t.lower_bound(9));
	// t.order_of_key(x) = 严格小于 x 的元素个数
	assert(t.order_of_key(11)==2);
	// t.find_by_order(k) = 第 k 个元素, 从 0 开始
	assert(*t.find_by_order(0)==8);
	t.join(t2); // 需 t 全小于或全大于 t2, 把 t2 并入 t
}
