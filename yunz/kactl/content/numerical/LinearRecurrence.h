/**
 * Description: 线性递推 $S_i = \sum_{j=0}^{n-1} tr_j S_{i-j-1}$ 求第 $k$ 项模 MOD, $k$ 可到 $10^{18}$.
 * 值在 $[0, MOD)$ 内. MOD 来自 BerlekampMassey.h (单独用时删掉 include, 自己定义 MOD).
 * Usage: // S 至少 n 项 (S[0..n-1]), tr 长 n, 下标从 0 开始
 * ll f=linearRec({0,1},{1,1},10); // 斐波那契 F(10)=55
 * vector<ll> tr=BM(s); // 先猜递推式, s 为暴力算的前几百项
 * ll v=linearRec(s,tr,k); // 第 k 项 (k 从 0 开始)
 * Time: O(n^2 \log k)
 */
#pragma once

#include "BerlekampMassey.h"

// a*b 对特征多项式取模, a, b 长 n+1
vector<ll>combine(const vector<ll>&a,const vector<ll>&b,
		const vector<ll>&tr){
	int n=tr.size();
	vector<ll>res(2*n+1);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			res[i+j]=(res[i+j]+a[i]*b[j])%MOD;
		}
	}
	for(int i=2*n;i>n;i--){
		for(int j=0;j<n;j++){
			res[i-1-j]=(res[i-1-j]+res[i]*tr[j])%MOD;
		}
	}
	res.resize(n+1);
	return res;
}
ll linearRec(vector<ll>S,vector<ll>tr,ll k){
	int n=tr.size();
	if(n==0){
		return 0;
	}
	vector<ll>pol(n+1),e(n+1);
	pol[0]=1;
	e[1]=1;
	for(k++;k;k>>=1){
		if(k&1){
			pol=combine(pol,e,tr);
		}
		e=combine(e,e,tr);
	}
	ll res=0;
	for(int i=0;i<n;i++){
		res=(res+pol[i+1]*S[i])%MOD;
	}
	return res;
}
