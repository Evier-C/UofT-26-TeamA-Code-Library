/**
 * Description: Berlekamp-Massey: 由数列前 $2n$ 项求出最短的线性递推式
 * (模素数 MOD). 返回 $C$ (下标从 0 开始), 满足 $s_i = \sum_j C_j s_{i-j-1}$.
 * 常用于暴力算出前若干项后猜递推式, 再配合 LinearRecurrence 求第 $k$ 项.
 * 输入须在 $[0, MOD)$ 内.
 * Usage: vector<ll> C=BM({0,1,1,3,5,11}); // C={1,2}
 * // 即 s[i]=s[i-1]+2*s[i-2]
 * Time: O(n^2)
 */
#pragma once

const ll MOD=998244353; // 素数模, 可改
ll qpow(ll a,ll b){
	ll r=1;
	for(a%=MOD;b;b>>=1,a=a*a%MOD)
		if(b&1)r=r*a%MOD;
	return r;
}
vector<ll>BM(vector<ll>s){
	int n=s.size(),L=0,m=0;
	if(n==0)return {};
	vector<ll>C(n),B(n),T;
	C[0]=B[0]=1;
	ll b=1;
	for(int i=0;i<n;i++){
		m++;
		ll d=s[i]%MOD; // 当前递推式的偏差
		for(int j=1;j<=L;j++)d=(d+C[j]*s[i-j])%MOD;
		if(!d)continue;
		T=C;
		ll coef=d*qpow(b,MOD-2)%MOD;
		for(int j=m;j<n;j++)
			C[j]=(C[j]+MOD-coef*B[j-m]%MOD)%MOD;
		if(2*L>i)continue;
		L=i+1-L;B=T;b=d;m=0;
	}
	C.resize(L+1);
	C.erase(C.begin());
	for(auto&x:C)x=(MOD-x)%MOD;
	return C;
}
