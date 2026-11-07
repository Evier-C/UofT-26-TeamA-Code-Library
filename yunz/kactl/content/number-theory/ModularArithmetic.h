/**
 * Description: 模质数 MOD 下的基本运算和组合数.
 * qpow(a, b) 返回 $a^b \bmod MOD$ ($a$ 可以为负, $b \ge 0$);
 * inv(a) 用费马小定理返回 $a^{MOD-2}$, 即 $a$ 的逆元, 要求 MOD 是质数且 $a$ 不是 MOD 的倍数;
 * init(n) 预处理 fac[i] $= i!$ 和 ifac[i] $= (i!)^{-1}$ ($0 \le i \le n$, $n < N$ 且 $n < $ MOD);
 * C(n, m) 返回 $\binom{n}{m} \bmod MOD$, $m < 0$ 或 $m > n$ 时返回 0, 要求 $n$ 不超过 init 的参数.
 * 加减法直接写 (a + b) \% MOD 和 (a - b + MOD) \% MOD.
 * 注意: 本文件的 inv 函数和 ModInverse 的 inv 数组同名, 不要同时复制.
 * Usage: init(1000000); // 只需调用一次, 参数取题目里 n 的最大值
 * ll c = C(5, 2); // 10
 * ll x = inv(3); // 3 的逆元
 * ll y = qpow(2, 100); // 2 的 100 次方模 MOD
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
