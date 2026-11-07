/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: 用 Tonelli-Shanks 算法求模平方根。求 $x$ 使 $x^2 = a \pmod p$（$-x$ 为另一个解）。
 * Usage: ll x = sqrt(a, p); // p 为质数 , 无解时 assert 失败
 * Time: 最坏 O(\log^2 p)，对大多数 $p$ 为 O(\log p)
 * Status: Tested for all a,p <= 10000
 */
#pragma once

#include "ModPow.h"

ll sqrt(ll a,ll p){
	a%=p;if(a<0)a+=p;
	if(a==0)return 0;
	assert(modpow(a,(p-1)/2,p)==1); // 否则无解
	if(p%4==3)return modpow(a,(p+1)/4,p);
	// 若 p % 8 == 5, 可用 a^(n+3)/8 或 2^(n+3)/8 * 2^(n-1)/4
	ll s=p-1,n=2;
	int r=0,m;
	while(s%2==0)
		++r,s/=2;
	/// 找一个模 p 的非二次剩余
	while(modpow(n,(p-1)/2,p)!=p-1)++n;
	ll x=modpow(a,(s+1)/2,p);
	ll b=modpow(a,s,p),g=modpow(n,s,p);
	for(;;r=m){
		ll t=b;
		for(m=0;m<r&&t!=1;++m)
			t=t*t%p;
		if(m==0)return x;
		ll gs=modpow(g,1LL<<(r-m-1),p);
		g=gs*gs%p;
		x=x*gs%p;
		b=b*g%p;
	}
}
