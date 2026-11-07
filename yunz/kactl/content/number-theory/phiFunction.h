/**
 * Description: 试除法求单个欧拉函数, $n \ge 1$. 要 $1..n$ 所有的 $\varphi$ 用 FastEratosthenes.
 * 扩展欧拉定理: $b \ge \varphi(n)$ 时 $a^b \equiv a^{b \bmod \varphi(n) + \varphi(n)} \pmod n$.
 * Usage: ll f = getPhi(12); // 4
 * ll e = b \% getPhi(n) + getPhi(n); // b 很大时降幂
 * Time: O(\sqrt n)
 */
#pragma once

ll getPhi(ll n){
	ll r=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i)continue;
		r=r/i*(i-1);
		while(n%i==0)n/=i;
	}
	if(n>1)r=r/n*(n-1);
	return r;
}
