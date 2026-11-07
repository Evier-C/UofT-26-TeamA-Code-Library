/**
 * Description: 确定性 Miller-Rabin 素性测试, 判断一个 long long 范围内的数是不是质数.
 * isPrime(n) 对所有 $n \le 9.2 \cdot 10^{18}$ 都正确 (用前 12 个质数 2..37 作底); $n < 2$ (包括负数) 返回 false.
 * 做法: 写 $n - 1 = d \cdot 2^s$, 对每个底 $a$ 看 $a^d, a^{2d}, \dots$ 中是否出现 1 或 $n - 1$.
 * 乘法用 \_\_int128 (mulmod), 自带 mulmod 和 powmod, 与 ModMulLL 相同, 一起复制时删掉一份.
 * 只判断 $10^7$ 以内的数时用线性筛更快.
 * Usage: if(isPrime(1000000007)) ... // true
 * bool b = isPrime(n); // n 为 long long
 * Time: 12 次快速幂, O(12 \log n)
 */
#pragma once

ll mulmod(ll a,ll b,ll m){return (__int128)a*b%m;}
ll powmod(ll a,ll b,ll m){
	ll r=1%m;
	a%=m;
	while(b){
		if(b&1)r=mulmod(r,a,m);
		a=mulmod(a,a,m);
		b>>=1;
	}
	return r;
}
bool isPrime(ll n){
	if(n<3||n%2==0)return n==2;
	ll d=n-1;
	int s=0;
	while(d%2==0){ // n - 1 = d * 2^s
		d/=2;
		s++;
	}
	for(ll a:{2,3,5,7,11,13,17,19,23,29,31,37}){
		if(n==a)return 1;
		ll x=powmod(a,d,n);
		if(x==1||x==n-1)continue;
		bool ok=0;
		for(int i=1;i<s&&!ok;i++){
			x=mulmod(x,x,n);
			if(x==n-1)ok=1;
		}
		if(!ok)return 0;
	}
	return 1;
}
