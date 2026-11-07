/**
 * Description: Berlekamp-Massey: 由数列前若干项 (模素数 MOD) 求最短线性递推式.
 * 递推阶数为 $n$ 时至少给前 $2n$ 项, 输入在 $[0, MOD)$ 内; 全 0 数列返回空.
 * Usage: vector<ll> s={0,1,1,3,5,11}; // 暴力算出的前若干项
 * vector<ll> C=BM(s); // C={1,2}, 阶数 L=C.size()
 * // s[i]=C[0]*s[i-1]+C[1]*s[i-2]+...+C[L-1]*s[i-L]
 * ll v=linearRec(s,C,k); // 第 k 项, 见 LinearRecurrence
 * Time: O(n^2), $n$ 为给出的项数
 */
#pragma once

const ll MOD=998244353; // 素数模, 可改
ll qpow(ll a,ll b){
	ll r=1;
	a%=MOD;
	while(b){
		if(b&1){
			r=r*a%MOD;
		}
		a=a*a%MOD;
		b>>=1;
	}
	return r;
}
vector<ll>BM(vector<ll>s){
	int n=s.size(),L=0,m=0;
	if(n==0){
		return {};
	}
	vector<ll>C(n),B(n),T;
	C[0]=1;
	B[0]=1;
	ll b=1;
	for(int i=0;i<n;i++){
		m++;
		ll d=s[i]%MOD; // 当前递推式的偏差
		for(int j=1;j<=L;j++){
			d=(d+C[j]*s[i-j])%MOD;
		}
		if(d==0){
			continue;
		}
		T=C;
		ll coef=d*qpow(b,MOD-2)%MOD;
		for(int j=m;j<n;j++){
			C[j]=(C[j]+MOD-coef*B[j-m]%MOD)%MOD;
		}
		if(2*L>i){
			continue;
		}
		L=i+1-L;
		B=T;
		b=d;
		m=0;
	}
	C.resize(L+1);
	C.erase(C.begin());
	for(auto&x:C){
		x=(MOD-x)%MOD;
	}
	return C;
}
