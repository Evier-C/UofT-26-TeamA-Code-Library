/**
 * Description: 快速沃尔什变换 (FWT), 求位运算卷积
 * $c_k = \sum_{i \oplus j = k} a_i b_j$, $\oplus$ 为 or, and, xor.
 * 下标从 0 开始, 长度 $n$ 须为 2 的幂 (不足补 0). $t=1$ 正变换,
 * $t=-1$ 逆变换. 取模时 xor 逆变换的 /2 改成乘 2 的逆元.
 * or 正变换即子集和 $\hat a_k = \sum_{i \subseteq k} a_i$; and 为超集和.
 * Usage: fwtXor(a,1); fwtXor(b,1); // a, b 等长
 * for(int i=0;i<n;i++) a[i]*=b[i];
 * fwtXor(a,-1); // a 即为 xor 卷积, or, and 同理
 * Time: O(n \log n)
 */
#pragma once

void fwtOr(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1)
		for(int i=0;i<n;i+=len<<1)
			for(int j=i;j<i+len;j++)a[j+len]+=t*a[j];
}
void fwtAnd(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1)
		for(int i=0;i<n;i+=len<<1)
			for(int j=i;j<i+len;j++)a[j]+=t*a[j+len];
}
void fwtXor(vector<ll>&a,int t){
	int n=a.size();
	for(int len=1;len<n;len<<=1)
		for(int i=0;i<n;i+=len<<1)
			for(int j=i;j<i+len;j++){
				ll u=a[j],v=a[j+len];
				a[j]=u+v;a[j+len]=u-v;
				if(t==-1)a[j]/=2,a[j+len]/=2;
			}
}
