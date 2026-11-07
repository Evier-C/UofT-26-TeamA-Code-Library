/**
 * Description: 可持久化线段树, 即主席树, 下标 [1, n]. 每次单点加产生一个新版本,
 * 只新建 $O(\log n)$ 个节点, 旧版本不变. 节点 0 是空树, rt[0] = 0.
 * 区间第 k 小: 把值离散化到 1..m, 版本 i 在 a[i] 处加 1, 则 rt[r] 减 rt[l - 1]
 * 就是 a[l..r] 中各值的出现次数.
 * Usage: rt[i] = update(rt[i - 1], 1, n, x, v); // 新版本: 第 x 位加 v
 * query(rt[i], 1, n, l, r); // 版本 i 中 [l, r] 的和
 * // 区间第 k 小: b 为排序去重后的值, m = b 的大小
 * rt[i] = update(rt[i - 1], 1, m, id(a[i]), 1); // id 从 1 开始
 * b[kth(rt[l - 1], rt[r], 1, m, k)]; // k 从 1 开始
 * 多组数据: tot = 0.
 * Time: O(\log N) 每次操作
 * Memory: O(N \log N)
 */
#pragma once

const int N=2e5+5,MX=N*20; // MX: 节点数, 约 N * (log n + 2)
int ls[MX],rs[MX],tot,rt[N];
ll sum[MX];
int update(int pre,int l,int r,int x,ll v){ // 返回新根
	int p=++tot;
	ls[p]=ls[pre],rs[p]=rs[pre],sum[p]=sum[pre]+v;
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
// 版本 v 减版本 u 中第 k 小的位置 (k 从 1 开始)
int kth(int u,int v,int l,int r,ll k){
	if(l==r)return l;
	int m=(l+r)>>1;
	ll c=sum[ls[v]]-sum[ls[u]];
	if(k<=c)return kth(ls[u],ls[v],l,m,k);
	return kth(rs[u],rs[v],m+1,r,k-c);
}
