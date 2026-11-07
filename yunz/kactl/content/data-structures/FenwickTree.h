/**
 * Description: 树状数组, 下标 1..n. 上半: 单点加, 前缀和, 二分找前缀和.
 * 下半: 区间加, 区间和, 用两个树状数组维护差分 d[i] 和 i * d[i].
 * 两半互相独立, 只抄需要的.
 * Usage: n = ...; // 多组数据: 把 c 或 c1, c2 的 1..n 清 0
 * add(x, v); // a[x] += v
 * ask(x); // a[1] + ... + a[x]
 * ask(r) - ask(l - 1); // a[l..r] 的和
 * search(s); // 最小的 x 使 a[1..x] 的和不小于 s, 要求 a 非负
 * rangeAdd(l, r, v); rangeSum(l, r); // 区间加, 区间和
 * Time: O(\log N)
 */
#pragma once

const int N=2e5+5; // 要求 n < 2^21
int n;
ll c[N];
void add(int x,ll v){for(;x<=n;x+=x&-x)c[x]+=v;}
ll ask(int x){
	ll r=0;
	for(;x;x-=x&-x)r+=c[x];
	return r;
}
int search(ll s){ // 不存在返回 n + 1
	int x=0;
	for(int i=1<<20;i;i>>=1)
		if(x+i<=n&&c[x+i]<s)x+=i,s-=c[x];
	return x+1;
}

ll c1[N],c2[N]; // 差分 d[i] 和 i * d[i]
void radd(int x,ll v){
	for(int i=x;i<=n;i+=i&-i)c1[i]+=v,c2[i]+=v*x;
}
void rangeAdd(int l,int r,ll v){radd(l,v),radd(r+1,-v);}
ll rsum(int x){ // a[1..x] 的和
	ll s=0;
	for(int i=x;i;i-=i&-i)s+=(x+1)*c1[i]-c2[i];
	return s;
}
ll rangeSum(int l,int r){return rsum(r)-rsum(l-1);}
