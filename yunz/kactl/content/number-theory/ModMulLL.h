/**
 * Description: 模数到 long long 上限 (约 $9.2 \cdot 10^{18}$) 的乘法和快速幂, 用 \_\_int128.
 * MillerRabin 里有同样的两个函数, 一起复制时删掉一份.
 * Usage: ll m = 1000000000000000003; // 大模数
 * ll x = mulmod(a, b, m); // a * b mod m, a 和 b 在 [0, m)
 * ll y = powmod(a, b, m); // a 的 b 次方 mod m, a, b 非负
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
