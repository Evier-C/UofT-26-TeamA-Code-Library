/**
 * Description: 主席树: 下标 [1, n] 单点加, 区间和, 每次修改产生新版本.
 * 节点 0 是全 0 的空树; 节点数 MX 约为 修改次数 * (log n + 2),
 * 默认够 2e5 次修改, 约 64MB, 对象必须是全局变量.
 * Usage: pst.tot = 0; // 多组数据清空, pst.rt[0] = 0 为空树
 * // 由版本 j 得到版本 i: a[x] 加 v
 * pst.rt[i] = pst.update(pst.rt[j], 1, n, x, v);
 * // 版本 i 中 a[l..r] 的和
 * ll s = pst.query(pst.rt[i], 1, n, l, r);
 * // 静态区间第 k 小, b[1..m] 为排序去重后的值
 * for (int i = 1; i <= n; i++) {
 *   int id = lower_bound(b + 1, b + m + 1, a[i]) - b;
 *   pst.rt[i] = pst.update(pst.rt[i - 1], 1, m, id, 1);
 * }
 * // a[l..r] 的第 k 小, k 从 1 开始
 * ll ans = b[pst.kth(pst.rt[l - 1], pst.rt[r], 1, m, k)];
 * Time: 每次操作 O(\log N)
 * Memory: O(N \log N)
 */
#pragma once

struct PST{
	static const int N=2e5+5;
	// MX: 节点数, 约 修改次数 * (log n + 2)
	static const int MX=N*20;
	int ls[MX],rs[MX],tot,rt[N];
	ll sum[MX];
	int update(int pre,int l,int r,int x,ll v){ // 返回新根
		int p=++tot;
		ls[p]=ls[pre];
		rs[p]=rs[pre];
		sum[p]=sum[pre]+v;
		if(l==r)return p;
		int m=(l+r)>>1;
		if(x<=m)ls[p]=update(ls[pre],l,m,x,v);
		else rs[p]=update(rs[pre],m+1,r,x,v);
		return p;
	}
	ll query(int p,int l,int r,int x,int y){ // [x, y] 的和
		if(!p||y<l||r<x)return 0;
		if(x<=l&&r<=y)return sum[p];
		int m=(l+r)>>1;
		return query(ls[p],l,m,x,y)+query(rs[p],m+1,r,x,y);
	}
	// 版本 v 减版本 u 中第 k 小的位置, k 从 1 开始
	int kth(int u,int v,int l,int r,ll k){
		if(l==r)return l;
		int m=(l+r)>>1;
		ll c=sum[ls[v]]-sum[ls[u]]; // 左半的个数
		if(k<=c)return kth(ls[u],ls[v],l,m,k);
		return kth(rs[u],rs[v],m+1,r,k-c);
	}
}pst;
