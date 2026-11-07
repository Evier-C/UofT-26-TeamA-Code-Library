/**
 * Description: 快速沃尔什变换 (FWT), 求位运算卷积 $c_k = \sum_{i \oplus j = k} a_i b_j$,
 * $\oplus$ 为 or, and, xor. 数组为 vector<ll>, 下标从 0 开始, 两个数组等长,
 * 长度 $n$ 必须是 2 的幂 (值域 $[0, 2^K)$ 就开 $n = 2^K$, 不足补 0).
 * 值用 ll 精确计算, 不取模 (注意结果别超过 long long).
 * \texttt{orConv / andConv / xorConv(a, b)}: 返回卷积结果, 长度 $n$, 不改原数组.
 * \texttt{fwtOr / fwtAnd / fwtXor(a, t)}: 原地变换, $t = 1$ 正变换, $t = -1$ 逆变换.
 * 含义: or 正变换即子集和 $\hat a_k = \sum_{i \subseteq k} a_i$; and 正变换即
 * 超集和 $\hat a_k = \sum_{i \supseteq k} a_i$; xor 正变换 $\hat a_k = \sum_i (-1)^{|i \cap k|} a_i$.
 * 正变换后逐点相乘再逆变换, 就是对应的卷积.
 * 取模版本: 每次加减后取模 (减法加 MOD), xor 逆变换的除以 2 改为乘
 * $inv2 = (MOD+1)/2$.
 * Usage: int n=1<<K; // 值域 [0,2^K)
 * vector<ll> a(n),b(n); // 填 a, b
 * vector<ll> c=xorConv(a,b); // c[k]=sum a[i]b[j], i xor j=k
 * vector<ll> d=orConv(a,b); // i or j=k
 * vector<ll> e=andConv(a,b); // i and j=k
 * fwtOr(a,1); // a 原地变为子集和, fwtOr(a,-1) 变回
 * Time: O(n \log n)
 */
#pragma once

void fwtOr(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1)
		for(int i=0;i<n;i+=len<<1)
			for(int j=i;j<i+len;j++)
				a[j+len]+=t*a[j];
}
void fwtAnd(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1)
		for(int i=0;i<n;i+=len<<1)
			for(int j=i;j<i+len;j++)
				a[j]+=t*a[j+len];
}
void fwtXor(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1){
		for(int i=0;i<n;i+=len<<1){
			for(int j=i;j<i+len;j++){
				ll u=a[j];
				ll v=a[j+len];
				a[j]=u+v;
				a[j+len]=u-v;
				if(t==-1){
					a[j]/=2;
					a[j+len]/=2;
				}
			}
		}
	}
}
vector<ll>orConv(vector<ll>a,vector<ll>b){
	fwtOr(a,1);
	fwtOr(b,1);
	for(int i=0;i<(int)a.size();i++)
		a[i]*=b[i];
	fwtOr(a,-1);
	return a;
}
vector<ll>andConv(vector<ll>a,vector<ll>b){
	fwtAnd(a,1);
	fwtAnd(b,1);
	for(int i=0;i<(int)a.size();i++)
		a[i]*=b[i];
	fwtAnd(a,-1);
	return a;
}
vector<ll>xorConv(vector<ll>a,vector<ll>b){
	fwtXor(a,1);
	fwtXor(b,1);
	for(int i=0;i<(int)a.size();i++)
		a[i]*=b[i];
	fwtXor(a,-1);
	return a;
}
