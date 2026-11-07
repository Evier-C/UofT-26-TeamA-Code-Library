/**
 * Description: 快速沃尔什变换 (FWT) 的三个变换, 用于位运算卷积
 * $c_k = \sum_{i \oplus j = k} a_i b_j$, $\oplus$ 为 or, and, xor.
 * 与 FWT.h 相同但不含卷积函数, 见 FWT.h 的说明. 长度须为 2 的幂,
 * 下标从 0 开始, ll 精确计算. $t = 1$ 正变换, $t = -1$ 逆变换.
 * Usage: fwtXor(a,1); // a, b 等长, 长度为 2 的幂
 * fwtXor(b,1);
 * for(int i=0;i<n;i++) a[i]*=b[i];
 * fwtXor(a,-1); // a 即为 xor 卷积, or, and 同理
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
