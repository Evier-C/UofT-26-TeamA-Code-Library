/**
 * Description: 线性递推求第 $k$ 项: 已知 $n$ 阶递推 $S_i = \sum_{j=0}^{n-1} tr_j S_{i-j-1}$
 * 和前 $n$ 项 $S_0..S_{n-1}$, 求 $S_k \bmod MOD$ ($k$ 从 0 开始, 可到 $10^{18}$).
 * 参数: S 至少 $n$ 项 (多给无妨), tr 长为 $n$ (系数顺序与 BM 的返回值相同),
 * 都下标从 0 开始, 值在 $[0, MOD)$ 内. tr 为空时数列全 0, 返回 0.
 * 原理: 求 $x^k$ 模特征多项式, 再与前 $n$ 项做线性组合, 比矩阵快速幂快.
 * MOD 来自 BerlekampMassey.h (单独使用时可删掉 include 自己定义 MOD).
 * Usage: ll f=linearRec({0,1},{1,1},10); // 第 10 个斐波那契数 55
 * vector<ll> s=...; // 暴力算出的前若干项
 * vector<ll> tr=BM(s); // 猜递推式
 * ll v=linearRec(s,tr,k); // 第 k 项
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
