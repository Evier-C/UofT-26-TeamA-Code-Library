/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description:
 * 在 $[a,b]$ 中找使 $f(i)$ 最大的最小的 i，前提是 $f(a) < \dots < f(i) \ge \dots \ge f(b)$。
 * 若要让另一侧允许非严格不等，把 (A) 处的 < 改为 <=，并把 (B) 处的循环反向。
 * 若要求最小值，把它改为 >，(B) 处同样修改。
 * Usage:
	int ind = ternSearch(0,n-1,[\&](int i){return a[i];});
 * Time: O(\log(b-a))
 * Status: tested
 */
#pragma once

template<class F>
int ternSearch(int a, int b, F f) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i; // (B)
	return a;
}
