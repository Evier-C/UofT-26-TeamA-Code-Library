/**
 * Description: 分治优化 DP (决策单调性). 把 $1..n$ 分成恰好 $m$ 段 (每段非空), 段 $[l, r]$ 的代价为 $w(l, r)$, 求最小总代价.
 * 转移: $f_j[i] = \min_{j-1 \le k < i} f_{j-1}[k] + w(k+1, i)$, 共 $m$ 层, 每层 $O(n \log n)$.
 * 条件: 最优的 $k$ 随 $i$ 单调不减; $w$ 满足四边形不等式 $w(a,c) + w(b,d) \le w(a,d) + w(b,c)$ ($a \le b \le c \le d$) 时成立.
 * dc(l, r, kl, kr) 求当前层的 f[l..r], 已知它们的最优 $k$ 都在 $[kl, kr]$ 内: 先暴力求中点 mid 的最优 $k$ (best),
 * 左半边的最优 $k$ 不超过 best, 右半边不小于 best. g 为上一层的结果, f 为当前层.
 * 例子: $w(l, r)$ 为区间和的平方 (前缀和 s), 按题目改 w. 要求 $1 \le m \le n$.
 * solveDP(n, m) 返回答案; 结束后 g[i] 为前 $i$ 个分成 $m$ 段的最小代价 ($i \ge m$; $m = 1$ 时 g[i] $= w(1, i)$).
 * Usage: // 读入 n, m, a[1..n]
 * for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
 * ll ans = solveDP(n, m); // 多组数据直接再调用
 * Time: O(m n \log n)
 */
#pragma once

const int N=1e5+5;
ll f[N],g[N],s[N];
ll w(int l,int r){ // 按题目改
	ll x=s[r]-s[l-1];
	return x*x;
}
// 求 f[l..r], 它们的最优 k 在 [kl, kr] 内
void dc(int l,int r,int kl,int kr){
	if(l>r)return;
	int mid=(l+r)/2;
	int best=kl;
	f[mid]=LLONG_MAX;
	for(int k=kl;k<=min(mid-1,kr);k++){
		ll v=g[k]+w(k+1,mid);
		if(v<f[mid]){
			f[mid]=v;
			best=k;
		}
	}
	dc(l,mid-1,kl,best);
	dc(mid+1,r,best,kr);
}
ll solveDP(int n,int m){
	for(int i=1;i<=n;i++)g[i]=w(1,i); // 第 1 层
	for(int j=2;j<=m;j++){
		dc(j,n,j-1,n-1);
		for(int i=j;i<=n;i++)g[i]=f[i];
	}
	return g[n];
}
