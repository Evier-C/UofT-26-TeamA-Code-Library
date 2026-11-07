/**
 * Description: 中国剩余定理, 解同余方程组 $x \equiv a_i \pmod {m_i}$, $i = 1..n$.
 * crt 要求 $m_i$ 两两互质: $x = \sum a_i M_i M_i^{-1}$, $M_i = M / m_i$.
 * excrt 允许任意模数: 逐个合并, 设当前解为 $x \bmod M$, 解
 * $M t \equiv a_i - x \pmod{m_i}$, 新解 $x + Mt$, 模数变为 $\text{lcm}(M, m_i)$.
 * 返回 $[0, \text{lcm})$ 内的最小解, 无解返回 $-1$. 要求 lcm 不超过 long long.
 * Usage: ll a[N], m[N]; // 下标从 1 开始, a[i] 可以为负
 * ll x = crt(a, m, n); // m 两两互质
 * ll y = excrt(a, m, n); // 任意 m, 无解为 -1
 * Time: O(n \log M)
 */
#pragma once

#include "euclid.h"

ll crt(ll*a,ll*m,int n){
	ll M=1,x=0;
	for(int i=1;i<=n;i++)M*=m[i];
	for(int i=1;i<=n;i++){
		ll Mi=M/m[i],t,y,r=(a[i]%m[i]+m[i])%m[i];
		exgcd(Mi%m[i],m[i],t,y); // t 为 Mi 模 m[i] 的逆元
		t=(__int128)((t%m[i]+m[i])%m[i])*r%m[i];
		x=(x+(__int128)Mi*t)%M;
	}
	return x;
}
ll excrt(ll*a,ll*m,int n){
	ll x=0,M=1; // 当前 x mod M
	for(int i=1;i<=n;i++){
		ll t,y,g=exgcd(M,m[i],t,y),c=((a[i]-x)%m[i]+m[i])%m[i];
		if(c%g)return -1;
		ll mg=m[i]/g;
		t=(__int128)((t%mg+mg)%mg)*(c/g)%mg;
		x+=M*t,M*=mg; // 新的 x 小于新的 M
	}
	return x;
}
