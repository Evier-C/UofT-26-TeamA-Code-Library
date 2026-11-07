/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: 由数列的前 $2n$ 项恢复出任意 $n$ 阶线性递推关系 (此处在模素数 \texttt{mod} 下计算).
 * 返回 $C$, 满足 $s[i] = \sum_j C[j] s[i-j-1]$.
 * 常用于暴力算出前若干项后猜线性递推式.
 * 理论上适用于任意域, 但用浮点数时不保证数值稳定.
 * 输出长度 $\le n$.
 * Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // 得 {1, 2}
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
#pragma once

#include "../number-theory/ModPow.h"

vector<ll>berlekampMassey(vector<ll>s){
	int n=sz(s),L=0,m=0;
	vector<ll>C(n),B(n),T;
	C[0]=B[0]=1;

	ll b=1;
	rep(i,0,n){++m;
		ll d=s[i]%mod;
		rep(j,1,L+1)d=(d+C[j]*s[i-j])%mod;
		if(!d)continue;
		T=C;ll coef=d*modpow(b,mod-2)%mod;
		rep(j,m,n)C[j]=(C[j]-coef*B[j-m])%mod;
		if(2*L>i)continue;
		L=i+1-L;B=T;b=d;m=0;
	}

	C.resize(L+1);C.erase(C.begin());
	for(ll&x:C)x=(mod-x)%mod;
	return C;
}
