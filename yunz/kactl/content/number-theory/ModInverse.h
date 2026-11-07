/**
 * Description: 线性求 $1..n$ 模质数 $p$ 的逆元, 要求 $n < p$, $n < N$.
 * 数组 inv 和 ModularArithmetic 的 inv 函数同名.
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
