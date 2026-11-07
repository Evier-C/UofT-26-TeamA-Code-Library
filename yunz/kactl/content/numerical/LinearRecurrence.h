/**
 * Description: 已知 $n$ 阶线性递推 $S_i = \sum_{j=0}^{n-1} tr_j S_{i-j-1}$ 及前 $n$ 项
 * $S_0..S_{n-1}$, 求第 $k$ 项 ($k$ 从 0 开始, 模 MOD). 用多项式取模快速幂,
 * 比矩阵快速幂快. MOD 来自 BerlekampMassey.h (可直接改成自己的常量).
 * Usage: ll f=linearRec({0,1},{1,1},k); // 第 k 个 Fibonacci
 * vector<ll> tr=BM(s); // 先猜递推式
 * ll v=linearRec(s,tr,k); // s 至少有 tr.size() 项
 * Time: O(n^2 \log k)
 */
#pragma once

#include "BerlekampMassey.h"

// 多项式 a*b 对特征多项式取模, a, b 长 n+1
vector<ll>combine(const vector<ll>&a,const vector<ll>&b,
		const vector<ll>&tr){
	int n=tr.size();
	vector<ll>res(2*n+1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			res[i+j]=(res[i+j]+a[i]*b[j])%MOD;
	for(int i=2*n;i>n;i--)
		for(int j=0;j<n;j++)
			res[i-1-j]=(res[i-1-j]+res[i]*tr[j])%MOD;
	res.resize(n+1);
	return res;
}
ll linearRec(vector<ll>S,vector<ll>tr,ll k){
	int n=tr.size();
	if(n==0)return 0; // 空递推: 全为 0
	vector<ll>pol(n+1),e(n+1);
	pol[0]=e[1]=1;
	for(k++;k;k>>=1){
		if(k&1)pol=combine(pol,e,tr);
		e=combine(e,e,tr);
	}
	ll res=0;
	for(int i=0;i<n;i++)res=(res+pol[i+1]*S[i])%MOD;
	return res;
}
