/**
 * Description: 快速幂, 返回 $a^b \bmod p$, 结果在 $[0, p)$ 内.
 * $a$ 可以为负或大于 $p$, $b \ge 0$, $p \ge 1$ ($p = 1$ 时返回 0).
 * 乘法用 long long, 要求 $p^2$ 不超过 long long, 即 $p$ 不超过约 $3 \cdot 10^9$;
 * 模数到 $10^{18}$ 时用 ModMulLL 的 powmod.
 * $p$ 是质数时 qpow(a, p - 2, p) 就是 $a$ 的逆元.
 * Usage: ll r = qpow(2, 10, 1000); // 24
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
