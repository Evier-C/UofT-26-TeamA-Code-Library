/**
 * Description: NTT 多项式乘法, 模 $998244353 = 119 \cdot 2^{23} + 1$, 原根 $g = 3$.
 * 系数下标从 0 开始, 输入须在 $[0, MOD)$ 内, 结果长度 $|a|+|b|-1 \le 2^{23}$.
 * ntt(f, 1) 正变换, ntt(f, -1) 逆变换 (已乘 $1/n$), $f$ 长度为 2 的幂.
 * 其他 NTT 模数 (原根都是 3): 469762049, 167772161, 1004535809.
 * 任意模数用 FFTMod.
 * Usage: vector<ll> a={1,2}, b={1,3};
 * vector<ll> c=nttConv(a,b); // c={1,5,6}
 * Time: O(n \log n)
 */
#pragma once

const ll MOD=998244353,G=3;
ll qpow(ll a,ll b){
	ll r=1;
	for(a%=MOD;b;b>>=1,a=a*a%MOD)
		if(b&1)r=r*a%MOD;
	return r;
}
void ntt(vector<ll>&f,int t){ // t=1 正变换, t=-1 逆变换
	int n=f.size();
	for(int i=1,j=0;i<n;i++){ // 位逆序置换
		for(int k=n>>1;(j^=k)<k;k>>=1);
		if(i<j)swap(f[i],f[j]);
	}
	for(int len=1;len<n;len<<=1){
		ll wn=qpow(G,(MOD-1)/(len<<1));
		if(t==-1)wn=qpow(wn,MOD-2);
		for(int i=0;i<n;i+=len<<1){
			ll w=1;
			for(int j=0;j<len;j++,w=w*wn%MOD){
				ll u=f[i+j],v=w*f[i+j+len]%MOD;
				f[i+j]=(u+v)%MOD;
				f[i+j+len]=(u-v+MOD)%MOD;
			}
		}
	}
	if(t==-1){
		ll inv=qpow(n,MOD-2);
		for(auto&v:f)v=v*inv%MOD;
	}
}
vector<ll>nttConv(vector<ll>a,vector<ll>b){
	if(a.empty()||b.empty())return {};
	int m=a.size()+b.size()-1,n=1;
	while(n<m)n<<=1;
	a.resize(n);b.resize(n);
	ntt(a,1);ntt(b,1);
	for(int i=0;i<n;i++)a[i]=a[i]*b[i]%MOD;
	ntt(a,-1);
	a.resize(m);
	return a;
}
