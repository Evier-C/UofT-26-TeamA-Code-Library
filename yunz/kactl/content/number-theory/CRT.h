/**
 * Description: 中国剩余定理, 解同余方程组 $x \equiv a_i \pmod{m_i}$, $i = 1..n$, 数组下标从 1 开始.
 * $a_i$ 可以为负或大于 $m_i$, 要求 $m_i \ge 1$. 两个函数都返回 $[0, L)$ 内最小的非负解, 其中 $L = \text{lcm}(m_1, \dots, m_n)$,
 * 所有解为 $x + kL$. 要求 $L$ 不超过 long long (约 $9.2 \cdot 10^{18}$), 中间乘法用 \_\_int128.
 * crt(a, m, n): $m_i$ 必须两两互质, $x = \sum a_i M_i M_i^{-1}$, $M = \prod m_i$, $M_i = M/m_i$, 逆元模 $m_i$ 求.
 * excrt(a, m, n): $m_i$ 任意, 无解返回 $-1$. 逐个合并: 设前面的解为 $x \bmod M$, 解 $Mt \equiv a_i - x \pmod{m_i}$
 * (用 exgcd, $g = \gcd(M, m_i)$ 不整除右边则无解), 新解 $x + Mt$, 新模数 $\text{lcm}(M, m_i)$.
 * 不确定是否互质时直接用 excrt. 依赖 euclid.h 的 exgcd.
 * Usage: ll a[N], m[N]; int n; // 读入 a[1..n], m[1..n]
 * ll x = crt(a, m, n); // m 两两互质
 * ll y = excrt(a, m, n); // 任意 m, 无解为 -1
 * Time: O(n \log L)
 */
#pragma once

#include "euclid.h"

ll crt(ll*a,ll*m,int n){
	ll M=1,x=0;
	for(int i=1;i<=n;i++)M*=m[i];
	for(int i=1;i<=n;i++){
		ll Mi=M/m[i];
		ll r=(a[i]%m[i]+m[i])%m[i];
		ll t,y;
		exgcd(Mi%m[i],m[i],t,y); // t 为 Mi 模 m[i] 的逆元
		t=(t%m[i]+m[i])%m[i];
		t=(__int128)t*r%m[i];
		x=(x+(__int128)Mi*t)%M;
	}
	return x;
}
ll excrt(ll*a,ll*m,int n){
	ll x=0,M=1; // 当前的解为 x mod M
	for(int i=1;i<=n;i++){
		ll c=((a[i]-x)%m[i]+m[i])%m[i];
		ll t,y;
		ll g=exgcd(M,m[i],t,y);
		if(c%g)return -1;
		ll mg=m[i]/g;
		t=(t%mg+mg)%mg;
		t=(__int128)t*(c/g)%mg;
		x+=M*t; // 新的 x 小于新的 M
		M*=mg;
	}
	return x;
}
