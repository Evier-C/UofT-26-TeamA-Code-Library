/**
 * Description: 离散对数. bsgs 求最小的 $x \ge 0$ 使 $c \cdot a^x \equiv b \pmod m$,
 * 要求 $\gcd(a, m) = 1$. exbsgs 求最小的 $x \ge 0$ 使 $a^x \equiv b \pmod m$,
 * $a, m$ 任意: 不断用 $d = \gcd(a, m)$ 同除 $a^x, b, m$ (若 $d \nmid b$ 无解),
 * 记下系数 $c = \prod (a/d)$, 直到 $a, m$ 互质, 再用 bsgs.
 * 无解返回 $-1$. $m$ 不超过约 $10^9$ (乘法不溢出).
 * Usage: ll x = bsgs(a, b, m); // gcd(a, m) = 1
 * ll y = exbsgs(a, b, m); // 任意 a, m, 无解为 -1
 * // a 的阶, 即最小的 k 使 a^k = 1, 为 bsgs(a, 1, m, a) + 1
 * Time: O(\sqrt m)
 */
#pragma once

ll bsgs(ll a,ll b,ll m,ll c=1){
	a%=m,b%=m,c%=m;
	if(c==b)return 0;
	ll t=sqrtl(m)+1,at=1;
	unordered_map<ll,ll>h; // b * a^j 对应的最大的 j
	for(ll j=0,cur=b;j<t;j++,cur=cur*a%m)h[cur]=j,at=at*a%m;
	// 找 c * a^(i t) = b * a^j, 则 x = i t - j
	for(ll i=1,cur=c;i<=t;i++){
		cur=cur*at%m;
		if(h.count(cur))return i*t-h[cur];
	}
	return -1;
}
ll exbsgs(ll a,ll b,ll m){
	a%=m,b%=m;
	if(b==1%m)return 0;
	ll k=0,c=1;
	for(ll d;(d=__gcd(a,m))!=1;){
		if(b%d)return -1;
		b/=d,m/=d,k++,c=c*(a/d)%m;
		if(c==b)return k; // x = k
	}
	ll x=bsgs(a,b,m,c);
	return x<0?-1:x+k;
}
