/**
 * Description: 中国剩余定理. 返回 $[0, \text{lcm})$ 内最小的解, 要求所有 $m_i$ 的 lcm 不超过 long long. 依赖 euclid.h.
 * Usage: ll a[N], m[N]; int n; // x = a[i] (mod m[i]), 下标从 1 开始
 * // a[i] 可以为负, m[i] 至少为 1
 * ll x = crt(a, m, n); // 要求 m 两两互质
 * ll y = excrt(a, m, n); // 任意 m, 无解为 -1
 * // 所有解为 y + k * lcm(m[1..n])
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
