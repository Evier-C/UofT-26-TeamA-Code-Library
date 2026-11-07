/**
 * Description: 模质数 MOD 下的常用函数: 快速幂, 费马小定理求逆元,
 * 预处理阶乘 fac 和阶乘逆元 ifac 求组合数.
 * 加减: (a + b) \% MOD, (a - b + MOD) \% MOD.
 * Usage: init(1000000); // 预处理 fac, ifac 到 n (n < N)
 * ll c = C(5, 2); // 10, m < 0 或 m > n 时为 0
 * ll x = inv(3); // 3 的逆元, 要求 MOD 是质数
 * Time: init O(N), C O(1), qpow 和 inv O(\log MOD)
 */
#pragma once

const ll MOD=998244353; // 或 1e9+7, 必须是质数
const int N=1e6+5;
ll fac[N],ifac[N];
ll qpow(ll a,ll b){ // a 的 b 次方模 MOD
	ll r=1;a%=MOD;if(a<0)a+=MOD;
	for(;b;b>>=1,a=a*a%MOD)if(b&1)r=r*a%MOD;
	return r;
}
ll inv(ll a){return qpow(a,MOD-2);} // a 不能是 MOD 的倍数
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
	ifac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%MOD;
}
ll C(int n,int m){
	if(m<0||m>n)return 0;
	return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;
}
