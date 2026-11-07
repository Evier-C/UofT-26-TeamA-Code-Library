/**
 * Description: 李超树, 整数 x 取值于 [lo, hi). 节点动态开点, 任意范围都无需离散化.
 * add 插入一条直线 $kx + m$, 或只在 [a, b) 上存在的线段. query 返回 x 处的最大值,
 * 若没有线段覆盖 x 则返回 LLONG\_MIN. 求最小值: 加入 $(-k, -m)$ 并对答案取负.
 * 要求 $|kx + m| < 9 \cdot 10^{18}$ 且 $C = hi - lo < 9 \cdot 10^{18}$.
 * Usage: LiChao lc(-1e9, 1e9 + 1);
 * lc.add({k, m}); lc.add({k, m}, a, b); lc.query(x);
 * Time: 每条直线或每次查询 O(\log C), 每条线段 O(\log^2 C)
 */
#pragma once

struct LiChao{
	struct L{
		ll k,m;
		ll operator()(ll x)const{return k*x+m;}
	};
	struct N{L f{0,LLONG_MIN};int c[2]{};};
	vector<N>t;ll lo,hi;
	LiChao(ll lo,ll hi):t(1),lo(lo),hi(hi){}
	int ch(int x,int d){
		if(!t[x].c[d])t[x].c[d]=sz(t),t.emplace_back();
		return t[x].c[d];
	}
	void add(L f,ll a=LLONG_MIN,ll b=LLONG_MAX){
		ins(0,lo,hi,a,b,f);
	}
	void ins(int x,ll l,ll r,ll a,ll b,L f){
		if(b<=l||r<=a)return;
		ll m=l+(r-l)/2;
		if(a<=l&&r<=b){
			if(f(m)>t[x].f(m))swap(f,t[x].f);
			if(r-l==1||f.k==t[x].f.k)return;
			int d=f.k>t[x].f.k;
			ins(ch(x,d),d?m:l,d?r:m,a,b,f);
		}else{
			if(a<m)ins(ch(x,0),l,m,a,b,f);
			if(b>m)ins(ch(x,1),m,r,a,b,f);
		}
	}
	ll query(ll v){
		ll res=LLONG_MIN,l=lo,r=hi;
		for(int x=0;;){
			res=max(res,t[x].f(v));
			ll m=l+(r-l)/2;
			int d=v>=m;
			if(!t[x].c[d])return res;
			x=t[x].c[d];
			(d?l:r)=m;
		}
	}
};
