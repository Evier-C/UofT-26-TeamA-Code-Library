/**
 * Description: 整除分块 (数论分块). 当 $i$ 从 1 到 $n$ 时 $\lfloor n/i \rfloor$ 只有 $O(\sqrt n)$ 种取值,
 * 把值相同的 $i$ 合成一段一起算. 下取整: 段的左端 $l$, 值 $q = \lfloor n/l \rfloor$, 右端 $r = \lfloor n/q \rfloor$.
 * 上取整: 值 $q = \lceil n/l \rceil$, $q > 1$ 时右端 $r = \lfloor (n-1)/(q-1) \rfloor$, $q = 1$ 时 $r = n$.
 * 两个数一起分块 (如求 $\sum \lfloor n/i \rfloor \lfloor m/i \rfloor$): $r = \min(\lfloor n/\lfloor n/l \rfloor \rfloor, \lfloor m/\lfloor m/l \rfloor \rfloor)$, 循环到 $\min(n, m)$.
 * 下面 floorSum(n) 求 $\sum_{i=1}^{n} \lfloor n/i \rfloor g(i)$, ceilSum(n) 求 $\sum_{i=1}^{n} \lceil n/i \rceil g(i)$,
 * 其中 sg(l, r) $= \sum_{i=l}^{r} g(i)$ 要按题目改 (例子里 $g = 1$; 莫比乌斯反演时 $g = \mu$, 用前缀和).
 * $n$ 到 $10^{12}$ 左右时注意结果是否超过 long long, 必要时取模.
 * Usage: ll s = floorSum(n); // sum floor(n/i) g(i)
 * ll t = ceilSum(n); // sum ceil(n/i) g(i)
 * for(ll l = 1, r; l <= n; l = r + 1) { // 直接写循环
 *   r = n / (n / l); // [l, r] 内 n/i 都相同
 * }
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
