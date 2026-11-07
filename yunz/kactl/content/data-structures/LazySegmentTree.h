/**
 * Usage: cin >> seg.n >> q;
 * for (int i = 1; i <= seg.n; i++) cin >> seg.a[i];
 * int n = seg.n;
 * seg.build(1, 1, n); // 建树, 多组数据每组都调用
 * seg.update(1, 1, n, l, r, v); // a[l..r] 都加 v
 * auto res = seg.query(1, 1, n, l, r); // 类型为 SegTree::Node
 * cout << res.sum << ' ' << res.mx; // 区间和, 区间最大值
 * Time: 建树 O(N), 修改和查询 O(\log N)
 */
#pragma once

struct SegTree{
	static const int N=2e5+5;
	struct Node{ll sum,mx;};
	int n;
	ll a[N];
	Node t[N<<2];
	ll lz[N<<2]; // 整段待加的值
	Node merge(Node x,Node y){ // 合并左右儿子
		return {x.sum+y.sum,max(x.mx,y.mx)};
	}
	void pushup(int p){t[p]=merge(t[p<<1],t[p<<1|1]);}
	void addtag(int p,int l,int r,ll v){ // 整段 [l, r] 都加 v
		t[p].sum+=v*(r-l+1);
		t[p].mx+=v;
		lz[p]+=v;
	}
	void pushdown(int p,int l,int r){
		if(!lz[p])return;
		int m=(l+r)>>1;
		addtag(p<<1,l,m,lz[p]);
		addtag(p<<1|1,m+1,r,lz[p]);
		lz[p]=0;
	}
	void build(int p,int l,int r){
		lz[p]=0;
		if(l==r){
			t[p]={a[l],a[l]};
			return;
		}
		int m=(l+r)>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		pushup(p);
	}
	void update(int p,int l,int r,int x,int y,ll v){ // 加 v
		if(x<=l&&r<=y){
			addtag(p,l,r,v);
			return;
		}
		pushdown(p,l,r);
		int m=(l+r)>>1;
		if(x<=m)update(p<<1,l,m,x,y,v);
		if(y>m)update(p<<1|1,m+1,r,x,y,v);
		pushup(p);
	}
	Node query(int p,int l,int r,int x,int y){ // [x, y]
		if(x<=l&&r<=y)return t[p];
		pushdown(p,l,r);
		int m=(l+r)>>1;
		if(y<=m)return query(p<<1,l,m,x,y);
		if(x>m)return query(p<<1|1,m+1,r,x,y);
		return merge(query(p<<1,l,m,x,y),query(p<<1|1,m+1,r,x,y));
	}
}seg;
