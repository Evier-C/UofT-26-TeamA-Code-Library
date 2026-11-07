/**
 * Description: 扩展 Lucas, 求 $\binom{n}{m} \bmod P$, $P$ 不必是质数. 把 $P$ 分解成 $p^k$,
 * 对每个 $p^k$ 去掉阶乘里所有的因子 $p$ 再单独算 $p$ 的次数, 最后用 CRT 合并.
 * 要求每个 $p^k$ 不太大 (约 $10^6$ 以内), $n, m$ 可以到 $10^{18}$.
 * Usage: ll c = exlucas(n, m, P); // m < 0 或 m > n 时返回 0
 * Time: O(\sum p^k \log n)
 */
#pragma once

#include "CRT.h"

ll pw(ll b,ll e,ll m){
	ll r=1%m;
	for(b%=m;e;e>>=1,b=b*b%m)
		if(e&1)r=r*b%m;
	return r;
}
ll inv(ll a,ll m){ll x,y;euclid(a,m,x,y);return (x%m+m)%m;}
ll fac(ll n,ll p,ll pk){ // n! 去掉所有因子 p 后模 pk
	if(!n)return 1;
	ll r=1;
	for(ll i=1;i<=pk;i++)if(i%p)r=r*i%pk;
	r=pw(r,n/pk,pk);
	for(ll i=1;i<=n%pk;i++)if(i%p)r=r*i%pk;
	return r*fac(n/p,p,pk)%pk;
}
ll Cpk(ll n,ll m,ll p,ll pk){
	ll e=0; // C(n, m) 中因子 p 的次数
	for(ll t=n;t;t/=p)e+=t/p;
	for(ll t=m;t;t/=p)e-=t/p;
	for(ll t=n-m;t;t/=p)e-=t/p;
	ll r=fac(n,p,pk)*inv(fac(m,p,pk),pk)%pk;
	return r*inv(fac(n-m,p,pk),pk)%pk*pw(p,e,pk)%pk;
}
ll exlucas(ll n,ll m,ll P){
	if(m<0||m>n)return 0;
	ll x=0,M=1;
	for(ll p=2,Q=P;Q>1;p++){
		if(p*p>Q)p=Q;
		if(Q%p)continue;
		ll pk=1;
		while(Q%p==0)Q/=p,pk*=p;
		x=crt(x,M,Cpk(n,m,p,pk),pk),M*=pk;
	}
	return x;
}
