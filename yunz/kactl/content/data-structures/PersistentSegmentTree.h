/**
 * Description: 可持久化线段树, 即主席树. 下标 [1, n], 每个节点存区间和.
 * 每次单点加都产生一个新版本, 即新根, 只新建 $O(\log n)$ 个节点, 旧版本不变,
 * 所以可以在任意历史版本上查询或继续修改. 节点 0 是全 0 的空树, rt[0] = 0.
 * update(pre, 1, n, x, v): 在版本 pre 的基础上 a[x] 加 v, 返回新版本的根.
 * query(p, 1, n, l, r): 版本 p 中 a[l..r] 的和.
 * kth(u, v, 1, n, k): 把版本 v 减去版本 u 看成计数数组, 返回其中第 k 小
 * 所在的下标, k 从 1 开始, 要求 k 不超过总个数.
 * 静态区间第 k 小: 值离散化到 1..m, 版本 i 在 id(a[i]) 处加 1,
 * 则 rt[r] 减 rt[l - 1] 就是 a[l..r] 中各值的出现次数.
 * 注意: 节点数 MX 约为 修改次数 * (log n + 2), 默认 N * 20 够 2e5 次修改;
 * 多组数据只需 tot = 0.
 * Usage: tot = 0; // 多组数据清空
 * // 例 1: 历史版本区间和
 * rt[i] = update(rt[j], 1, n, x, v); // 由版本 j 得到版本 i
 * ll s = query(rt[i], 1, n, l, r); // 版本 i 中 a[l..r] 的和
 * // 例 2: 静态区间第 k 小, b[1..m] 为排序去重后的值
 * for (int i = 1; i <= n; i++) {
 *   int id = lower_bound(b + 1, b + m + 1, a[i]) - b;
 *   rt[i] = update(rt[i - 1], 1, m, id, 1);
 * }
 * ll ans = b[kth(rt[l - 1], rt[r], 1, m, k)]; // a[l..r] 第 k 小
 * Time: 每次操作 O(\log N)
 * Memory: O(N \log N)
 */
#pragma once

const int N=2e5+5;
const int MX=N*20; // 节点数, 约 修改次数 * (log n + 2)
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
