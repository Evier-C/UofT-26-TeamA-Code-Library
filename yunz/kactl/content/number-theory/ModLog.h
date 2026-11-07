/**
 * Description: 离散对数 (BSGS, 大步小步). 解 $a^x \equiv b \pmod m$, 返回最小的 $x \ge 0$, 无解返回 $-1$.
 * bsgs(a, b, m, c) 解 $c \cdot a^x \equiv b \pmod m$, 要求 $\gcd(a, m) = 1$, $c$ 默认为 1.
 * 设 $t = \lfloor \sqrt m \rfloor + 1$, 把 $b \cdot a^j$ ($0 \le j < t$) 存进哈希表,
 * 再枚举 $i = 1..t$ 找 $c \cdot a^{it} = b \cdot a^j$, 得 $x = it - j$.
 * exbsgs(a, b, m) 对任意 $a, m$ 解 $a^x \equiv b \pmod m$: 每次取 $d = \gcd(a, m)$,
 * 若 $d \nmid b$ 无解, 否则 $b, m$ 同除以 $d$, 系数 $c$ 乘上 $a/d$, $x$ 的偏移 $k$ 加一,
 * 直到 $a, m$ 互质后用 bsgs 求剩下的部分, 答案加 $k$.
 * 注意 $x = 0$ 时 $a^0 = 1$, 所以 $b \equiv 1$ 时答案是 0.
 * 所有输入取模后计算, $a, b$ 可以大于 $m$, 但不能为负. $m$ 不超过约 $10^9$, 否则乘法要改 \_\_int128.
 * Usage: ll x = bsgs(3, 13, 17); // gcd(a, m) = 1, 3^x = 13 (mod 17)
 * ll y = exbsgs(a, b, m); // 任意 a, m, 无解为 -1
 * // a 的阶, 即最小的 k 使 a^k = 1, 为 bsgs(a, 1, m, a) + 1
 * Time: O(\sqrt m)
 */
#pragma once

ll bsgs(ll a,ll b,ll m,ll c=1){
	a%=m;
	b%=m;
	c%=m;
	if(c==b)return 0;
	ll t=sqrtl(m)+1;
	ll at=1; // a^t
	unordered_map<ll,ll>h; // b * a^j 对应的最大的 j
	ll cur=b;
	for(ll j=0;j<t;j++){
		h[cur]=j;
		cur=cur*a%m;
		at=at*a%m;
	}
	// 找 c * a^(i t) = b * a^j, 则 x = i t - j
	cur=c;
	for(ll i=1;i<=t;i++){
		cur=cur*at%m;
		if(h.count(cur))return i*t-h[cur];
	}
	return -1;
}
ll exbsgs(ll a,ll b,ll m){
	a%=m;
	b%=m;
	if(b==1%m)return 0;
	ll k=0,c=1;
	while(true){
		ll d=__gcd(a,m);
		if(d==1)break;
		if(b%d)return -1;
		b/=d;
		m/=d;
		k++;
		c=c*(a/d)%m;
		if(c==b)return k; // x = k
	}
	ll x=bsgs(a,b,m,c);
	if(x<0)return -1;
	return x+k;
}
