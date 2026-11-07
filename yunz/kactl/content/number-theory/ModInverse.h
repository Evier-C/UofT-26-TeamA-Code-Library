/**
 * Description: 线性求 $1..n$ 模质数 $p$ 的逆元, 要求 $n < p$.
 * 原理: $p = \lfloor p/i \rfloor \cdot i + (p \bmod i)$.
 * 单个数的逆元用快速幂 $a^{p-2}$ 或 exgcd.
 * Usage: initInv(n, p); // 之后 inv[i] 为 i 的逆元, 1 到 n
 * Time: O(N)
 */
#pragma once

const int N=1e6+5;
ll inv[N];
void initInv(int n,ll p){
	inv[1]=1;
	for(int i=2;i<=n;i++)inv[i]=(p-p/i)*inv[p%i]%p;
}
