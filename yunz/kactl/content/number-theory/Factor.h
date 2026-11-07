/**
 * Description: Pollard-rho 质因数分解, $n$ 到 $9.2 \cdot 10^{18}$. 依赖 MillerRabin. 随机数生成器叫 prng.
 * Usage: vector<ll> f;
 * factor(2299, f); // f = {11, 19, 11}, 含重复, 顺序任意
 * sort(f.begin(), f.end()); // 相同的质因子挨在一起
 * // n = 1 时 f 不变; 多次调用会追加到 f, 先 f.clear()
 * Time: 期望 O(n^{1/4} \log n)
 */
#pragma once

#include "MillerRabin.h"

mt19937_64 prng(20261107);
// n 为合数, 返回 n 的一个因子, 可能是 n
ll rho(ll n){
	if(n%2==0)return 2;
	ll c=prng()%(n-1)+1;
	ll s=0,t=0,v=1;
	for(int g=1;;g<<=1){
		for(int k=1;k<=g;k++){
			t=((__int128)t*t+c)%n;
			v=mulmod(v,abs(t-s),n);
			if(k%127==0){
				ll d=__gcd(v,n);
				if(d>1)return d;
			}
		}
		ll d=__gcd(v,n);
		if(d>1)return d;
		s=t;
		v=1;
	}
}
void factor(ll n,vector<ll>&f){
	if(n==1)return;
	if(isPrime(n)){
		f.push_back(n);
		return;
	}
	ll d=n;
	while(d==n)d=rho(n);
	factor(d,f);
	factor(n/d,f);
}
