/**
 * Description: \emph{欧拉函数} $\varphi(n)$ 为 $1..n$ 中与 $n$ 互质的数的个数.
 * $n = p_1^{k_1} \cdots p_r^{k_r}$ 时 $\varphi(n) = n \prod_{p|n}(1-1/p)$;
 * $m, n$ 互质时 $\varphi(mn)=\varphi(m)\varphi(n)$.
 * $\sum_{d|n} \varphi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \varphi(n)/2$ ($n>1$).
 *
 * \textbf{欧拉定理}: $a,n$ 互质 $\Rightarrow a^{\varphi(n)} \equiv 1 \pmod{n}$.
 * \textbf{扩展欧拉定理}: $b \ge \varphi(n)$ 时 $a^b \equiv a^{b \bmod \varphi(n) + \varphi(n)} \pmod n$.
 * \textbf{费马小定理}: $p$ 为质数 $\Rightarrow a^{p} \equiv a \pmod{p}$.
 *
 * 下面的 getPhi 用试除法求单个 $\varphi(n)$; 要求 $1..n$ 所有的
 * $\varphi$ 用 FastEratosthenes 的线性筛.
 * Usage: ll f = getPhi(n); // n 至少为 1
 * Time: O(\sqrt n)
 */
#pragma once

ll getPhi(ll n){
	ll r=n;
	for(ll i=2;i*i<=n;i++)if(n%i==0){
		r=r/i*(i-1);
		while(n%i==0)n/=i;
	}
	if(n>1)r=r/n*(n-1);
	return r;
}
