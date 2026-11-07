/**
 * Description: NTT 多项式乘法, 模 $998244353 = 119 \cdot 2^{23} + 1$, 原根 $g = 3$, 不依赖其他文件.
 * \texttt{nttConv(a, b)}: 输入两个 vector<ll>, 下标从 0 开始, 值必须在 $[0, MOD)$ 内
 * (负数先加 MOD); 返回 $c_k = \sum_{i+j=k} a_i b_j \bmod MOD$, 长度 $|a|+|b|-1$
 * (须 $\le 2^{23}$). 任一为空返回空.
 * \texttt{ntt(f, 1)} 正变换, \texttt{ntt(f, -1)} 逆变换 (已乘 $1/n$), $f$ 长度须为 2 的幂.
 * 换模数只改 MOD 和 G, 其他 NTT 模数 (原根都是 3): 469762049, 167772161, 1004535809.
 * 要精确整数结果用 FFT; 任意模数 (如 $10^9+7$) 用 FFTMod.
 * Usage: vector<ll> a={1,2},b={1,3}; // 1+2x, 1+3x
 * vector<ll> c=nttConv(a,b); // c={1,5,6}
 * Time: O(n \log n), $n = |a|+|b|$
 */
#pragma once

const ll MOD=998244353;
const ll G=3; // 原根
ll qpow(ll a,ll b){
	ll r=1;
	a%=MOD;
	while(b){
		if(b&1)
			r=r*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return r;
}
void ntt(vector<ll>&f,int t){ // t=1 正变换, t=-1 逆变换
	int n=f.size();
	vector<int>rev(n); // 位逆序置换
	for(int i=1;i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1)
			rev[i]|=n>>1;
	}
	for(int i=0;i<n;i++)
		if(i<rev[i])
			swap(f[i],f[rev[i]]);
	for(int len=1;len<n;len<<=1){
		ll wn=qpow(G,(MOD-1)/(len<<1)); // 2len 次单位根
		if(t==-1)
			wn=qpow(wn,MOD-2);
		for(int i=0;i<n;i+=len<<1){
			ll w=1;
			for(int j=0;j<len;j++){
				ll u=f[i+j];
				ll v=w*f[i+j+len]%MOD;
				f[i+j]=(u+v)%MOD;
				f[i+j+len]=(u-v+MOD)%MOD;
				w=w*wn%MOD;
			}
		}
	}
	if(t==-1){
		ll inv=qpow(n,MOD-2);
		for(auto&v:f)
			v=v*inv%MOD;
	}
}
vector<ll>nttConv(vector<ll>a,vector<ll>b){
	if(a.empty()||b.empty())
		return {};
	int m=a.size()+b.size()-1;
	int n=1;
	while(n<m)
		n<<=1;
	a.resize(n);
	b.resize(n);
	ntt(a,1);
	ntt(b,1);
	for(int i=0;i<n;i++)
		a[i]=a[i]*b[i]%MOD;
	ntt(a,-1);
	a.resize(m);
	return a;
}
