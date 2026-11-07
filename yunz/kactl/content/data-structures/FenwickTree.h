/**
 * Description: 树状数组, 下标 1..n. 两个结构体互相独立, 只抄需要的.
 * BIT, 全局对象 bit, 单点加, 前缀和: init(n) 设长度并清空;
 * add(x, v) 令 a[x] 加 v; ask(x) 返回 a[1..x] 的和,
 * a[l..r] 的和为 ask(r) - ask(l - 1); search(s) 返回最小的 x 使 a[1..x]
 * 的和不小于 s, 不存在返回 n + 1, 要求所有 a 非负. 常用于求第 s 小:
 * a[v] 为值 v 的个数, search(s) 即第 s 小的值.
 * RangeBIT, 全局对象 rbit, 区间加, 区间和: init(n) 设长度并清空;
 * rangeAdd(l, r, v) 令 a[l..r] 都加 v; rangeSum(l, r) 返回 a[l..r] 的和.
 * 原理: 维护差分 d[i] 的两个树状数组, c1 存 d[i], c2 存 i * d[i].
 * 初值: BIT 对每个 i 调用 add(i, a[i]); RangeBIT 调用 rangeAdd(i, i, a[i]).
 * 注意: 要求 $n < 2^{21}$; 下标不能为 0; 多组数据重新 init.
 * 对象要定义在全局; 要第二个就在全局再写 BIT bit2;
 * Usage: bit.init(n); // 每组数据先 init
 * for (int i = 1; i <= n; i++) bit.add(i, a[i]); // 建树
 * bit.add(x, v); // a[x] += v
 * ll s = bit.ask(r) - bit.ask(l - 1); // a[l..r] 的和
 * int x = bit.search(k); // 前缀和第一次不小于 k 的位置
 * rbit.init(n); // 区间版
 * for (int i = 1; i <= n; i++) rbit.rangeAdd(i, i, a[i]);
 * rbit.rangeAdd(l, r, v); ll t = rbit.rangeSum(l, r);
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
