/**
 * Description: 线性基. xb 的值在 $[0, 2^{63})$; rb 是区间线性基, 值在 $[0, 2^{31})$ (要 ll 把 B 改成 63, int 改成 ll).
 * 两个对象都要是全局的, 第二个写 XorBasis xb2;. rb 在 N = 5e5 时约 124MB. rb 只能在末尾加数.
 * \textbf{关于 0} (按题意选):
 * (1) 非空子集能异或出 0 $\iff$ xb.cnt $>$ xb.rk (某次 insert 返回 false); 区间上 $\iff r - l + 1 >$ rb.rank(l, r).
 * (2) 允许空集时 0 总能得到. check(0) 总是 true (空集), 问非空子集时用 (1).
 * (3) kth(k, z): $z$ 为 0 算不算一个值, 非空子集取 cnt $>$ rk, 允许空集取 true. $z$ 为 true 时第 1 小是 0, 其余顺延.
 * (4) qmin() 是非空子集的最小值: 能得到 0 时为 0, 否则为最低的基向量. qmax 不受影响.
 * Usage: xb.init(); // 多组数据也调用它
 * for(int i = 1; i <= n; i++) xb.insert(a[i]);
 * bool ind = xb.insert(x); // false: x 能被前面的数异或出
 * bool c = xb.check(x); // x 能否被异或出
 * ll mx = xb.qmax(); // 最大异或和
 * bool zero = xb.cnt > xb.rk; // 非空子集能否异或出 0
 * ll mn = xb.qmin(); // 非空子集最小, 没插过数为 -1
 * int rk = xb.rk; // 秩, 不同的异或值有 2^rk 个, 含 0
 * xb.rebuild(); // kth 之前调用, 之后再 insert 要再调
 * ll v = xb.kth(k, xb.cnt > xb.rk); // 非空子集第 k 小
 * ll w = xb.kth(k, true); // 允许空集, 第 1 小是 0
 * // k 从 1 开始, 不存在时为 -1
 * rb.init();
 * for(int i = 1; i <= n; i++) rb.add(a[i]); // 加到末尾
 * int q = rb.qmax(l, r); // a[l..r] 的最大异或和
 * int t = rb.rank(l, r); // a[l..r] 的秩
 * bool z = r - l + 1 > rb.rank(l, r); // 区间能否异或出 0
 * bool c2 = rb.check(l, r, x); // x 能否由 a[l..r] 异或出
 * Time: insert, check, qmax, kth, add 和区间查询 O(B), rebuild O(B^2)
 */
#pragma once

struct XorBasis{
	static const int B=63; // 位 0..62
	ll p[B]; // p[i] 为最高位是 i 的基向量, 没有为 0
	int cnt,rk; // 插入的个数, 基的大小
	void init(){
		memset(p,0,sizeof p);
		cnt=0;
		rk=0;
	}
	bool insert(ll x){
		cnt++;
		for(int i=B-1;i>=0;i--){
			if(!(x>>i&1))continue;
			if(!p[i]){
				p[i]=x;
				rk++;
				return true;
			}
			x^=p[i];
		}
		return false; // x 被消成 0
	}
	bool check(ll x){
		for(int i=B-1;i>=0;i--){
			if(!(x>>i&1))continue;
			if(!p[i])return false;
			x^=p[i];
		}
		return true;
	}
	ll qmax(){
		ll r=0;
		for(int i=B-1;i>=0;i--)r=max(r,r^p[i]);
		return r;
	}
	ll qmin(){ // 非空子集, 没有插过数时返回 -1
		if(cnt>rk)return 0;
		for(int i=0;i<B;i++){
			if(p[i])return p[i];
		}
		return -1;
	}
	void rebuild(){ // 每个 p[i] 只在自己的最高位上有其他基的位
		for(int i=0;i<B;i++){
			for(int j=i-1;j>=0;j--){
				if(p[i]>>j&1)p[i]^=p[j];
			}
		}
	}
	// 第 k 小的不同异或值, z 表示 0 算不算, 不存在返回 -1
	ll kth(ll k,bool z){
		if(z){
			if(k==1)return 0;
			k--;
		}
		if(rk<B&&k>=(1LL<<rk))return -1;
		ll r=0;
		int t=0; // 第 t 个基, 从小到大
		for(int i=0;i<B;i++){
			if(!p[i])continue;
			if(k>>t&1)r^=p[i];
			t++;
		}
		return r;
	}
}xb;

struct RangeXorBasis{
	static const int N=5e5+5,B=31;
	// p[r][i]: 前缀 a[1..r] 的基, pos 为它来自的下标, 尽量靠右
	int n,p[N][B],pos[N][B];
	void init(){n=0;} // p[0], pos[0] 一直是 0
	void add(int x){
		n++;
		memcpy(p[n],p[n-1],sizeof p[n]);
		memcpy(pos[n],pos[n-1],sizeof pos[n]);
		int ps=n;
		for(int i=B-1;i>=0;i--){
			if(!(x>>i&1))continue;
			if(!p[n][i]){
				p[n][i]=x;
				pos[n][i]=ps;
				return;
			}
			if(pos[n][i]<ps){ // 换成更靠右的
				swap(p[n][i],x);
				swap(pos[n][i],ps);
			}
			x^=p[n][i];
		}
	}
	int qmax(int l,int r){
		int res=0;
		for(int i=B-1;i>=0;i--){
			if(pos[r][i]>=l)res=max(res,res^p[r][i]);
		}
		return res;
	}
	int rank(int l,int r){
		int k=0;
		for(int i=0;i<B;i++){
			if(pos[r][i]>=l)k++;
		}
		return k;
	}
	bool check(int l,int r,int x){
		for(int i=B-1;i>=0;i--){
			if(!(x>>i&1))continue;
			if(pos[r][i]<l)return false;
			x^=p[r][i];
		}
		return true;
	}
}rb;
