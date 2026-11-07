/**
 * Description: 整除分块. $\lfloor n/i \rfloor$ 只有 $O(\sqrt n)$ 种取值,
 * 值为 $q = \lfloor n/l \rfloor$ 的一段是 $[l, \lfloor n/q \rfloor]$.
 * 上取整: $q = \lceil n/l \rceil > 1$ 时段的右端是 $\lfloor (n-1)/(q-1) \rfloor$, $q = 1$ 时到 $n$.
 * 两个数一起分块 (如 $\lfloor n/i \rfloor \lfloor m/i \rfloor$): $r = \min(n/(n/l), m/(m/l))$, $l \le \min(n, m)$.
 * 例子求 $\sum_{i=1}^{n} \lfloor n/i \rfloor g(i)$, sg(l, r) 为 $g$ 的区间和, 按题目改.
 * Usage: ll s = floorSum(n); // sum floor(n/i) g(i), i 从 1 到 n
 * ll t = ceilSum(n); // sum ceil(n/i) g(i), i 从 1 到 n
 * Time: O(\sqrt N)
 */
#pragma once

ll sg(ll l,ll r){return r-l+1;} // g 的区间和, 这里 g = 1
ll floorSum(ll n){
	ll res=0;
	for(ll l=1,r;l<=n;l=r+1){
		ll q=n/l;
		r=n/q; // [l, r] 内 n/i 都等于 q
		res+=q*sg(l,r);
	}
	return res;
}
ll ceilSum(ll n){
	ll res=0;
	for(ll l=1,r;l<=n;l=r+1){
		ll q=(n+l-1)/l;
		r=q>1?(n-1)/(q-1):n; // [l, r] 内上取整都是 q
		res+=q*sg(l,r);
	}
	return res;
}
