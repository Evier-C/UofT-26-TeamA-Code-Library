/**
 * Description: 拉格朗日插值 (模 MOD $= 998244353$, 自带 qpow): 不求系数直接求单点值.
 * 多项式次数必须不超过点数 $-1$; $x_i$ 模 MOD 互不相同, $y_i$ 在 $[0, MOD)$ 内.
 * 典型用法: 答案是 $d$ 次多项式时, 暴力算 $d+1$ 个点再插值.
 * 与 NTT, BM 同时使用时 MOD 和 qpow 重名, 删掉一份.
 * Usage: vector<ll> x={1,2,3},y={1,4,9}; // f(x)=x^2
 * ll v=lagrange(x,y,10); // f(10)=100, O(n^2)
 * vector<ll> a=lagrangeCoef(x,y); // 系数 a={0,0,1}
 * // 点为 0..n 时 O(n): ys[i]=f(i), i=0..n, k 可到 1e18
 * ll w=lagrangeSeq(ys,k);
 * // 点为 1..n+1 时: ys[0] 存 f(1), 调用 lagrangeSeq(ys,k-1)
 * // 例: S(m)=1^K+...+m^K 是 K+1 次多项式
 * vector<ll> s(K+2); // s[j]=S(j), j=0..K+1
 * for(int j=1;j<=K+1;j++)
 *   s[j]=(s[j-1]+qpow(j,K))\%MOD;
 * ll ans=lagrangeSeq(s,m); // S(m) mod MOD
 * Time: lagrange, lagrangeCoef 为 O(n^2 + n \log MOD); lagrangeSeq 为 O(n + \log MOD)
 */
#pragma once

const ll MOD=998244353;
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
ll md(ll v){ // 取模到 [0, MOD)
	return (v%MOD+MOD)%MOD;
}
ll lagrange(const vector<ll>&x,const vector<ll>&y,ll k){
	int n=x.size();
	ll res=0;
	for(int i=0;i<n;i++){
		ll num=y[i]; // 分子
		ll den=1; // 分母
		for(int j=0;j<n;j++){
			if(j==i)
				continue;
			num=num*md(k-x[j])%MOD;
			den=den*md(x[i]-x[j])%MOD;
		}
		res=(res+num*qpow(den,MOD-2))%MOD;
	}
	return res;
}
ll lagrangeSeq(const vector<ll>&y,ll k){
	int n=(int)y.size()-1;
	if(k>=0&&k<=n)
		return y[k];
	k%=MOD;
	vector<ll>pre(n+2),suf(n+2),fac(n+1),ifac(n+1);
	pre[0]=1; // pre[i]=(k-0)(k-1)...(k-(i-1))
	for(int i=0;i<=n;i++)
		pre[i+1]=pre[i]*md(k-i)%MOD;
	suf[n+1]=1; // suf[i]=(k-i)(k-i-1)...(k-n)
	for(int i=n;i>=0;i--)
		suf[i]=suf[i+1]*md(k-i)%MOD;
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%MOD;
	ifac[n]=qpow(fac[n],MOD-2);
	for(int i=n;i>=1;i--)
		ifac[i-1]=ifac[i]*i%MOD;
	ll res=0;
	for(int i=0;i<=n;i++){
		ll t=y[i]*pre[i]%MOD*suf[i+1]%MOD;
		t=t*ifac[i]%MOD*ifac[n-i]%MOD;
		if((n-i)&1) // 分母符号 (-1)^(n-i)
			res=(res-t+MOD)%MOD;
		else
			res=(res+t)%MOD;
	}
	return res;
}
vector<ll>lagrangeCoef(const vector<ll>&x,const vector<ll>&y){
	int n=x.size();
	vector<ll>P(n+1),res(n),q(n);
	P[0]=1; // P(x)=(x-x_0)(x-x_1)...(x-x_{n-1})
	for(int j=0;j<n;j++){
		ll c=md(x[j]);
		for(int d=j+1;d>=1;d--)
			P[d]=md(P[d-1]-c*P[d]);
		P[0]=md(-c*P[0]);
	}
	for(int i=0;i<n;i++){
		ll c=md(x[i]);
		q[n-1]=P[n]; // q = P / (x - x_i)
		for(int d=n-1;d>=1;d--)
			q[d-1]=(P[d]+c*q[d])%MOD;
		ll den=1;
		for(int j=0;j<n;j++)
			if(j!=i)
				den=den*md(x[i]-x[j])%MOD;
		ll coef=y[i]*qpow(den,MOD-2)%MOD;
		for(int d=0;d<n;d++)
			res[d]=(res[d]+coef*q[d])%MOD;
	}
	return res;
}
