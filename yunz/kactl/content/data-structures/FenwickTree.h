/**
 * Description: 树状数组, 下标 1..n, 全局 n 为长度. 两个版本互相独立, 只抄需要的.
 * 版本 1, 单点加, 前缀和: add(x, v) 令 a[x] 加 v; ask(x) 返回 a[1..x] 的和,
 * a[l..r] 的和为 ask(r) - ask(l - 1); search(s) 返回最小的 x 使 a[1..x]
 * 的和不小于 s, 不存在返回 n + 1, 要求所有 a 非负. 常用于求第 s 小:
 * a[v] 为值 v 的个数, search(s) 即第 s 小的值.
 * 版本 2, 区间加, 区间和: rangeAdd(l, r, v) 令 a[l..r] 都加 v;
 * rangeSum(l, r) 返回 a[l..r] 的和. 原理: 维护差分 d[i] 的两个树状数组,
 * c1 存 d[i], c2 存 i * d[i].
 * 初值: 版本 1 对每个 i 调用 add(i, a[i]); 版本 2 调用 rangeAdd(i, i, a[i]).
 * 注意: 要求 $n < 2^{21}$; 下标不能为 0; 多组数据把 c 或 c1, c2 的 1..n 清 0.
 * Usage: n = ...; // 多组数据先把 c[1..n] 清 0
 * for (int i = 1; i <= n; i++) add(i, a[i]); // 建树
 * add(x, v); // a[x] += v
 * ll s = ask(r) - ask(l - 1); // a[l..r] 的和
 * int x = search(k); // 前缀和第一次不小于 k 的位置
 * // 版本 2: 先把 c1[1..n], c2[1..n] 清 0
 * for (int i = 1; i <= n; i++) rangeAdd(i, i, a[i]);
 * rangeAdd(l, r, v); ll t = rangeSum(l, r);
 * Time: 每次操作 O(\log N)
 */
#pragma once

const int N=2e5+5; // 要求 n < 2^21
int n;
ll c[N];
void add(int x,ll v){
	for(;x<=n;x+=x&-x)c[x]+=v;
}
ll ask(int x){ // a[1..x] 的和
	ll r=0;
	for(;x;x-=x&-x)r+=c[x];
	return r;
}
int search(ll s){ // 不存在返回 n + 1
	int x=0;
	for(int i=1<<20;i;i>>=1){
		if(x+i<=n&&c[x+i]<s){
			x+=i;
			s-=c[x];
		}
	}
	return x+1;
}

ll c1[N],c2[N]; // 差分 d[i] 和 i * d[i]
void radd(int x,ll v){
	for(int i=x;i<=n;i+=i&-i){
		c1[i]+=v;
		c2[i]+=v*x;
	}
}
void rangeAdd(int l,int r,ll v){
	radd(l,v);
	radd(r+1,-v);
}
ll rsum(int x){ // a[1..x] 的和
	ll s=0;
	for(int i=x;i;i-=i&-i)s+=(x+1)*c1[i]-c2[i];
	return s;
}
ll rangeSum(int l,int r){return rsum(r)-rsum(l-1);}
