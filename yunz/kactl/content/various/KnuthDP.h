/**
 * Description: 区间 DP 的 Knuth 优化 (四边形不等式优化), 把 $O(n^3)$ 的区间 DP 降到 $O(n^2)$.
 * 适用的转移: $f[l][r] = \min_{l \le k < r} (f[l][k] + f[k+1][r]) + w(l, r)$, $f[i][i] = 0$, 答案 $f[1][n]$.
 * 条件: 对所有 $a \le b \le c \le d$ 有 $w(a,c) + w(b,d) \le w(a,d) + w(b,c)$ (四边形不等式) 且 $w(b,c) \le w(a,d)$ (区间包含单调).
 * 此时最优分割点满足 $opt[l][r-1] \le opt[l][r] \le opt[l+1][r]$, 只在这个范围内枚举 $k$.
 * 例子是石子合并: $w(l, r)$ 为 $a_l..a_r$ 的和, 用前缀和 s; 按题目改 w 即可.
 * 调用 knuth(n) 后 f[l][r] 为区间 $[l, r]$ 的答案, opt[l][r] 为它的最优分割点 (左半边是 $[l, k]$).
 * 环形问题把数组复制一倍, 求 $\min f[i][i+n-1]$. 求最大值时一般不满足条件, 不要直接改成 max.
 * 多组数据不需要清空 (用到的 f, opt 都会重新算).
 * Usage: // 读入 n 和 a[1..n]
 * for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
 * ll ans = knuth(n); // f[1][n]
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
