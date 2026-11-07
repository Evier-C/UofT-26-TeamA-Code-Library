/**
 * Description: 可持久化线段树, 下标 [0, n), 单点修改, 区间查询. upd 返回新根,
 * 旧根仍然有效. 根 0 为空树. 按需修改 T, f, unit.
 * kth 要求 f 为加法, 且版本 i 存的是 a[0..i) 中各值的出现次数.
 * Usage: PST t(n); vi rt = {0};
 * rt.push_back(t.upd(rt.back(), p, v)); // a[p] = f(a[p], v)
 * t.query(rt[i], l, r); // 版本 i 中 [l, r) 的 f 值
 * t.kth(rt[l], rt[r], k); // a[l..r) 第 k 小, k 从 0 起
 * Time: O(\log N)
 */
#pragma once

struct PST{
	typedef ll T;
	static constexpr T unit=0;
	T f(T a,T b){return a+b;}
	struct N{T v;int l,r;};
	vector<N>t={{unit,0,0}};int n;
	PST(int n):n(n){}
	int upd(int x,int p,T v,int l=0,int r=-1){
		if(r<0)r=n;
		N c=t[x];
		if(r-l==1)c.v=f(c.v,v);
		else{
			int m=(l+r)/2;
			if(p<m)c.l=upd(c.l,p,v,l,m);
			else c.r=upd(c.r,p,v,m,r);
			c.v=f(t[c.l].v,t[c.r].v);
		}
		t.push_back(c);
		return sz(t)-1;
	}
	T query(int x,int b,int e,int l=0,int r=-1){
		if(r<0)r=n;
		if(!x||e<=l||r<=b)return unit;
		if(b<=l&&r<=e)return t[x].v;
		int m=(l+r)/2;
		return f(query(t[x].l,b,e,l,m),query(t[x].r,b,e,m,r));
	}
	int kth(int a,int b,T k,int l=0,int r=-1){
		if(r<0)r=n;
		if(r-l==1)return l;
		int m=(l+r)/2;
		T c=t[t[b].l].v-t[t[a].l].v;
		if(k<c)return kth(t[a].l,t[b].l,k,l,m);
		return kth(t[a].r,t[b].r,k-c,m,r);
	}
};
