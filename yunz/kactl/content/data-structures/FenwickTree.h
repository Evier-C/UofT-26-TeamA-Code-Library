/**
 * Description: 树状数组 BIT: 单点加, 前缀和; RangeBIT: 区间加, 区间和;
 * 下标 1..n, 互相独立. 要求 $n < 2^{21}$, 对象要定义在全局.
 * Usage: bit.init(n); // 每组数据先 init
 * for (int i = 1; i <= n; i++) bit.add(i, a[i]); // 建树
 * bit.add(x, v); // a[x] += v
 * ll s = bit.ask(r) - bit.ask(l - 1); // a[l..r] 的和
 * // 最小的 x 使 a[1..x] 的和不小于 k, 没有则 n + 1, 要求 a 非负
 * int x = bit.search(k);
 * rbit.init(n); // 区间版
 * for (int i = 1; i <= n; i++) rbit.rangeAdd(i, i, a[i]);
 * rbit.rangeAdd(l, r, v); // a[l..r] 都加 v
 * ll t = rbit.rangeSum(l, r); // a[l..r] 的和
 * Time: 每次操作 O(\log N)
 */
#pragma once

struct BIT{
	static const int N=2e5+5; // 要求 n < 2^21
	int n;
	ll c[N];
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++)c[i]=0;
	}
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
}bit;

struct RangeBIT{
	static const int N=2e5+5;
	int n;
	ll c1[N],c2[N]; // 差分 d[i] 和 i * d[i]
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++){
			c1[i]=0;
			c2[i]=0;
		}
	}
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
}rbit;
