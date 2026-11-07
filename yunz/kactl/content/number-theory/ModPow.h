/**
 * Description: 快速幂, 求 $a^b \bmod p$. 要求 $p^2$ 不超过 long long,
 * 即 $p$ 不超过约 $3 \cdot 10^9$; 更大的模数用 ModMulLL 的 powmod.
 * Usage: ll r = qpow(a, b, p); // a 可以为负, b 至少为 0
 * Time: O(\log b)
 */
#pragma once

ll qpow(ll a,ll b,ll p){
	ll r=1%p;a%=p;if(a<0)a+=p;
	for(;b;b>>=1,a=a*a%p)if(b&1)r=r*a%p;
	return r;
}
