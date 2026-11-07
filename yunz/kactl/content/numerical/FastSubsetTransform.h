/**
 * Description: FWT 的三个变换 (同 FWT.h, 不含卷积函数), 用 ll 精确计算.
 * Usage: // a, b 等长, 长度 n 为 2 的幂, 下标从 0 开始
 * fwtXor(a,1); // 正变换
 * fwtXor(b,1);
 * for(int i=0;i<n;i++) a[i]*=b[i];
 * fwtXor(a,-1); // 逆变换, a 即为 xor 卷积
 * // or, and 卷积换成 fwtOr, fwtAnd
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
