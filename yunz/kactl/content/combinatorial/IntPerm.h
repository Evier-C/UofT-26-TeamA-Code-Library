/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: 把排列转成整数 (不保持字典序). 整数转排列可以查表.
 * Usage: vi v = {2, 0, 1}; int r = permToInt(v);
 * // v 为 0..n-1 的排列, r 属于 [0, n!), n 不超过 12
 * Time: O(n)
 */
#pragma once

int permToInt(vi& v) {
	int use = 0, i = 0, r = 0;
	for(int x:v) r = r * ++i + __builtin_popcount(use & -(1<<x)),
		use |= 1 << x;                     // 注意是负号, 非 ~
	return r;
}
