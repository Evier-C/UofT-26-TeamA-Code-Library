/**
 * Description: 线性时间求 $1, 2, \dots, n$ 模质数 $p$ 的逆元, 要求 $p$ 是质数且 $n < p$.
 * 原理: 由 $p = \lfloor p/i \rfloor \cdot i + (p \bmod i)$ 得 $i^{-1} = -\lfloor p/i \rfloor \cdot (p \bmod i)^{-1}$.
 * initInv(n, p) 之后 inv[i] 为 $i$ 模 $p$ 的逆元 ($1 \le i \le n$, $n < N$).
 * 只求单个数的逆元用快速幂 $a^{p-2}$ (ModPow) 或 exgcd (euclid, 模数可以不是质数).
 * 注意: 数组名 inv 和 ModularArithmetic 的 inv 函数同名.
 * Usage: initInv(1000000, 1000000007); // 多组数据不用重新算
 * ll x = inv[5]; // 5 的逆元, 5 * x \% p 等于 1
 * Time: O(n)
 */
#pragma once

const int N=1e6+5;
ll inv[N];
void initInv(int n,ll p){
	inv[1]=1;
	for(int i=2;i<=n;i++)inv[i]=(p-p/i)*inv[p%i]%p;
}
