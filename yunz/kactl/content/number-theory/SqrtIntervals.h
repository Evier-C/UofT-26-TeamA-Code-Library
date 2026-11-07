/**
 * Description: 整除分块. 按题目改 sg(l, r) $= \sum_{i=l}^{r} g(i)$ (例子 $g = 1$), 注意结果溢出.
 * 上取整的段: $q = \lceil n/l \rceil > 1$ 时 $r = \lfloor (n-1)/(q-1) \rfloor$, 否则 $r = n$.
 * Usage: ll s = floorSum(n); // sum floor(n/i) * g(i), i 从 1 到 n
 * ll t = ceilSum(n); // sum ceil(n/i) * g(i)
 * for(ll l = 1, r; l <= n; l = r + 1) { // 直接写循环
 *   r = n / (n / l); // [l, r] 内 n/i 都等于 n/l
 * }
 * // 两个数 n, m 一起分块: l 到 min(n, m),
 * // r = min(n / (n / l), m / (m / l))
 * Time: O(\sqrt n) 次 sg
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
		if(q>1)r=(n-1)/(q-1); // [l, r] 内上取整都是 q
		else r=n;
		res+=q*sg(l,r);
	}
	return res;
}
