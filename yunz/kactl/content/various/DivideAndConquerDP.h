/**
 * Description: 分治优化 DP: 把 $1..n$ 分成恰好 $m$ 段 (每段非空), 段 $[l, r]$ 代价 $w(l, r)$, 求最小总代价.
 * 要求最优分割点单调 ($w$ 满足四边形不等式即可). 例子是区间和的平方, 按题目改 w.
 * Usage: // 读入 n, m, a[1..n], m 从 1 到 n
 * for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
 * ll ans = solveDP(n, m); // 多组数据直接再调用
 * g[i]; // 前 i 个分成 m 段的最小代价 (i 至少为 m)
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
