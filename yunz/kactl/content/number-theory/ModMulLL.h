/**
 * Description: 模数 $m$ 在 long long 范围内 (到约 $9 \cdot 10^{18}$) 的
 * 乘法和快速幂, 用 \_\_int128 防止溢出.
 * Usage: ll x = mulmod(a, b, m); // a * b mod m, 要求 a, b 在 [0, m)
 * ll y = powmod(a, b, m); // a 的 b 次方 mod m
 * Time: mulmod O(1), powmod O(\log b)
 */
#pragma once

ll mulmod(ll a,ll b,ll m){return (__int128)a*b%m;}
ll powmod(ll a,ll b,ll m){
	ll r=1%m;a%=m;
	for(;b;b>>=1,a=mulmod(a,a,m))if(b&1)r=mulmod(r,a,m);
	return r;
}
