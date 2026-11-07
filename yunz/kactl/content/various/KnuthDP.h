/**
 * Description: 区间 DP 的 Knuth 优化 (四边形不等式).
 * $f[l][r] = \min_{l \le k < r} (f[l][k] + f[k+1][r]) + w(l, r)$.
 * 若对 $a \le b \le c \le d$ 有 $w(a,c) + w(b,d) \le w(a,d) + w(b,c)$ 且
 * $w(b,c) \le w(a,d)$, 则最优分割点 $opt[l][r-1] \le opt[l][r] \le opt[l+1][r]$,
 * 只在这个范围里枚举 $k$, 总复杂度 $O(n^2)$. 例子是石子合并, $w$ 为区间和.
 * Usage: // 读入 n, s[i] = s[i-1] + a[i]; 按题目改 w
 * ll ans = knuth(n); // f[1][n]
 * Time: O(N^2)
 * Memory: N = 3005 时约 110MB
 */
#pragma once

const int N=3005;
ll f[N][N],s[N];
int opt[N][N]; // f[l][r] 的最优分割点
ll w(int l,int r){return s[r]-s[l-1];} // 按题目改
ll knuth(int n){
	for(int i=1;i<=n;i++)f[i][i]=0,opt[i][i]=i;
	for(int len=2;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++){
			f[l][r]=LLONG_MAX;
			int R=min(r-1,opt[l+1][r]);
			for(int k=opt[l][r-1];k<=R;k++){
				ll v=f[l][k]+f[k+1][r]+w(l,r);
				if(v<f[l][r])f[l][r]=v,opt[l][r]=k;
			}
		}
	return f[1][n];
}
