/**
 * Description: 快速幂 $a^b \bmod p$. 要求 $p$ 不超过约 $3 \cdot 10^9$ (乘法不溢出), 更大的模数用 ModMulLL 的 powmod.
 * Usage: ll r = qpow(2, 10, 1000); // 24, 结果在 [0, p) 内
 * ll s = qpow(-3, 5, 7); // a 可以为负, b 至少为 0
 * ll iv = qpow(a, p - 2, p); // p 为质数时 a 的逆元
 * Time: O(\log b)
 */
#pragma once

ll qpow(ll a,ll b,ll p){
	ll r=1%p;
	a%=p;
	if(a<0)a+=p;
	while(b){
		if(b&1)r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
