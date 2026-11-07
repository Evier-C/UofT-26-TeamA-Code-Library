/**
 * Description: \emph{欧拉函数} $\varphi(n)$ 为 $1..n$ 中与 $n$ 互质的数的个数.
 * $n = p_1^{k_1} \cdots p_r^{k_r}$ 时 $\varphi(n) = n \prod_{p|n}(1-1/p)$; $\varphi(p^k) = (p-1)p^{k-1}$;
 * $m, n$ 互质时 $\varphi(mn)=\varphi(m)\varphi(n)$.
 * $\sum_{d|n} \varphi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \varphi(n)/2$ ($n>1$).
 *
 * \textbf{欧拉定理}: $a,n$ 互质 $\Rightarrow a^{\varphi(n)} \equiv 1 \pmod{n}$.
 * \textbf{扩展欧拉定理}: $b \ge \varphi(n)$ 时 $a^b \equiv a^{b \bmod \varphi(n) + \varphi(n)} \pmod n$ ($a, n$ 任意), 用于指数很大的幂.
 * \textbf{费马小定理}: $p$ 为质数 $\Rightarrow a^{p} \equiv a \pmod{p}$.
 *
 * getPhi(n) 用试除法求单个 $\varphi(n)$, 要求 $1 \le n \le 9 \cdot 10^{18}$, 复杂度 $O(\sqrt n)$ ($n$ 到 $10^{14}$ 左右还能接受).
 * 要 $1..n$ 所有的 $\varphi$ 时用 FastEratosthenes 的线性筛.
 * Usage: ll f = getPhi(12); // 4
 * ll e = b \% getPhi(n) + getPhi(n); // 扩展欧拉定理降幂
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
