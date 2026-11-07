/**
 * Description: 模质数 MOD 下的快速幂, 逆元, 组合数. MOD 必须是质数, init 的 $n < N$ 且 $n < $ MOD.
 * inv 函数和 ModInverse 的 inv 数组同名, 不要同时复制.
 * Usage: init(1000000); // 预处理 fac, ifac 到 n, 只需调用一次
 * ll c = C(5, 2); // 10, m < 0 或 m > n 时为 0
 * ll x = inv(3); // 3 的逆元, a 不能是 MOD 的倍数
 * ll y = qpow(2, 100); // 2 的 100 次方, a 可以为负
 * fac[i]; ifac[i]; // i 的阶乘, 阶乘的逆元
 * ll s = (a + b) \% MOD, d = (a - b + MOD) \% MOD; // 加减
 * Time: init O(n), C O(1), qpow 和 inv O(\log MOD)
 */
#pragma once

const ll MOD=998244353; // 或 1e9+7, 必须是质数
const int N=1e6+5;
ll fac[N],ifac[N];
ll qpow(ll a,ll b){ // a 的 b 次方模 MOD
	ll r=1;
	a%=MOD;
	if(a<0)a+=MOD;
	while(b){
		if(b&1)r=r*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return r;
}
ll inv(ll a){return qpow(a,MOD-2);}
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
