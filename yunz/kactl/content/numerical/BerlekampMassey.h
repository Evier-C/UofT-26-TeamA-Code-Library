/**
 * Description: Berlekamp-Massey: 给出数列 $s_0, s_1, \dots$ 的前若干项 (模素数 MOD),
 * 求最短的线性递推式. 若真实递推阶数为 $n$, 至少要给前 $2n$ 项.
 * 返回 vector<ll> C (下标从 0 开始, 长度即阶数 $L$), 满足对所有 $i \ge L$:
 * $s_i = \sum_{j=0}^{L-1} C_j s_{i-j-1} \pmod{MOD}$. 数列全为 0 时返回空.
 * 典型用法: 暴力或 DP 算出前几百项, BM 猜出递推式, 再用 LinearRecurrence
 * 求第 $k$ 项. 输入须在 $[0, MOD)$ 内; MOD 必须是素数 (要求逆元).
 * Usage: vector<ll> s={0,1,1,3,5,11};
 * vector<ll> C=BM(s); // C={1,2}
 * // 即 s[i]=s[i-1]+2*s[i-2]
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
