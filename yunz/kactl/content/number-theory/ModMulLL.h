/**
 * Description: 模数 $m$ 很大 (到 long long 上限, 约 $9.2 \cdot 10^{18}$) 时的乘法和快速幂.
 * 直接 a * b \% m 会溢出, 这里先转成 \_\_int128 再取模.
 * mulmod(a, b, m) 返回 $ab \bmod m$, 要求 $0 \le a, b < m$ (负数先调到 $[0, m)$).
 * powmod(a, b, m) 返回 $a^b \bmod m$, 要求 $a \ge 0$, $b \ge 0$, $m \ge 1$.
 * 注意: MillerRabin 里有完全相同的两个函数, 两个文件都复制时删掉一份.
 * Usage: ll m = 1000000000000000003; // 大模数
 * ll x = mulmod(a, b, m); // a * b mod m
 * ll y = powmod(a, b, m); // a 的 b 次方 mod m
 * Time: mulmod O(1), powmod O(\log b)
 */
#pragma once

ll mulmod(ll a,ll b,ll m){return (__int128)a*b%m;}
ll powmod(ll a,ll b,ll m){
	ll r=1%m;
	a%=m;
	while(b){
		if(b&1)r=mulmod(r,a,m);
		a=mulmod(a,a,m);
		b>>=1;
	}
	return r;
}
