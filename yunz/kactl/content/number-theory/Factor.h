/**
 * Description: Pollard-rho 质因数分解. rho 用 $f(x) = x^2 + c$ 的倍增找环,
 * 每 127 步做一次 gcd. 结果含重复的质因子, 顺序任意.
 * Usage: vector<ll> f; factor(n, f); sort(f.begin(), f.end());
 * // 2299 得到 11 11 19, n = 1 时为空
 * Time: 期望 O(n^{1/4})
 */
#pragma once

#include "MillerRabin.h"

mt19937_64 prng(20261107);
ll rho(ll n){ // n 为合数, 返回 n 的一个因子, 可能是 n
	if(n%2==0)return 2;
	ll c=prng()%(n-1)+1,s=0,t=0,v=1;
	for(int g=1;;g<<=1,s=t,v=1){
		for(int k=1;k<=g;k++){
			t=((__int128)t*t+c)%n;
			v=mulmod(v,abs(t-s),n);
			if(k%127==0){ll d=__gcd(v,n);if(d>1)return d;}
		}
		ll d=__gcd(v,n);
		if(d>1)return d;
	}
}
void factor(ll n,vector<ll>&f){
	if(n==1)return;
	if(isPrime(n)){f.push_back(n);return;}
	ll d=n;
	while(d==n)d=rho(n);
	factor(d,f),factor(n/d,f);
}
