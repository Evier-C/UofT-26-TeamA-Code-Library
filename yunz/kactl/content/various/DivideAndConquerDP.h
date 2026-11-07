/**
 * Description: 分治优化 DP. 把 $1..n$ 分成 $m$ 段 (每段非空), 段 $[l, r]$ 的代价为 $w(l, r)$:
 * $f_j[i] = \min_{k < i} f_{j-1}[k] + w(k+1, i)$. 若最优的 $k$ 随 $i$ 单调不减
 * ($w$ 满足四边形不等式时成立), 先求中点 $mid$ 的最优 $k$, 左半边的 $k$
 * 不超过它, 右半边不小于它. g 为上一层, f 为当前层.
 * Usage: // 读入 n, a[i], 按题目改 w
 * ll ans = solveDP(n, m); // 分成 m 段的最小代价, m 不超过 n
 * Time: O(m N \log N)
 */
#pragma once

const int N=1e5+5;
ll f[N],g[N],s[N];
ll w(int l,int r){ll x=s[r]-s[l-1];return x*x;} // 按题目改
// 求 f[l..r], 它们的最优 k 在 [kl, kr] 内
void dc(int l,int r,int kl,int kr){
	if(l>r)return;
	int mid=(l+r)/2,best=kl;
	f[mid]=LLONG_MAX;
	for(int k=kl;k<=min(mid-1,kr);k++){
		ll v=g[k]+w(k+1,mid);
		if(v<f[mid])f[mid]=v,best=k;
	}
	dc(l,mid-1,kl,best),dc(mid+1,r,best,kr);
}
ll solveDP(int n,int m){
	for(int i=1;i<=n;i++)g[i]=w(1,i); // 第 1 层
	for(int j=2;j<=m;j++){
		dc(j,n,j-1,n-1);
		for(int i=j;i<=n;i++)g[i]=f[i];
	}
	return g[n];
}
