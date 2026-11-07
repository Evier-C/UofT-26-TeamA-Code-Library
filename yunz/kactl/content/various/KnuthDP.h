/**
 * Description: 区间 DP 的 Knuth 优化: $f[l][r] = \min_{l \le k < r} (f[l][k] + f[k+1][r]) + w(l, r)$.
 * 要求 $w(a,c) + w(b,d) \le w(a,d) + w(b,c)$ 且 $w(b,c) \le w(a,d)$ ($a \le b \le c \le d$). 例子是石子合并, 按题目改 w.
 * Usage: // 读入 n 和 a[1..n]
 * for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
 * ll ans = knuth(n); // f[1][n]
 * f[l][r]; opt[l][r]; // 区间答案, 最优分割点 k, 左边是 [l, k]
 * // 多组数据不用清空
 * Time: O(n^2)
 * Memory: N = 3005 时约 110MB
 */
#pragma once

const int N=3005;
ll f[N][N],s[N];
int opt[N][N]; // f[l][r] 的最优分割点
ll w(int l,int r){return s[r]-s[l-1];} // 按题目改
ll knuth(int n){
	for(int i=1;i<=n;i++){
		f[i][i]=0;
		opt[i][i]=i;
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			f[l][r]=LLONG_MAX;
			int R=min(r-1,opt[l+1][r]);
			for(int k=opt[l][r-1];k<=R;k++){
				ll v=f[l][k]+f[k+1][r]+w(l,r);
				if(v<f[l][r]){
					f[l][r]=v;
					opt[l][r]=k;
				}
			}
		}
	}
	return f[1][n];
}
