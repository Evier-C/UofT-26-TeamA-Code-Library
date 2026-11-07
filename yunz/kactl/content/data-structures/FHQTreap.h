/**
 * Description: FHQ treap, 两种用法: 按值的可重集合, 或按位置的序列, 支持区间翻转,
 * 区间和. 不要混在同一棵树上. N 为插入总次数, 删掉的节点不回收;
 * kth, pre, nxt 要保证答案存在; 对象必须是全局变量.
 * Usage: tr.tot = tr.root = 0; // 多组数据清空
 * // 用法 1: 可重集合
 * tr.insert(5); tr.insert(3); tr.insert(5);
 * tr.erase(5); // 删一个 5, 没有则不变
 * int r = tr.getrank(5); // 小于 5 的个数 + 1, 这里为 2
 * ll v = tr.kth(1); // 第 1 小, 为 3
 * ll p = tr.pre(5), q = tr.nxt(3); // 前驱 3, 后继 5
 * // 用法 2: 序列 a[1..n], 位置从 1 开始
 * for (int i = 1; i <= n; i++)
 *   tr.root = tr.merge(tr.root, tr.newnode(a[i]));
 * tr.reverse(l, r); // 翻转 a[l..r]
 * ll s = tr.rangeSum(l, r); // a[l..r] 的和
 * vector<ll> o; tr.dfs(tr.root, o); // o 为当前序列
 * Time: 每次操作期望 O(\log N)
 */
#pragma once

struct Treap{
	static const int N=2e5+5; // 插入总次数
	int ls[N],rs[N],siz[N],tot,root;
	unsigned rnd[N];
	ll val[N],sum[N];
	bool rev[N];
	mt19937 rng{12345};
	int newnode(ll v){
		int p=++tot;
		ls[p]=0;
		rs[p]=0;
		siz[p]=1;
		rev[p]=0;
		rnd[p]=rng();
		val[p]=v;
		sum[p]=v;
		return p;
	}
	void pushup(int p){
		siz[p]=siz[ls[p]]+siz[rs[p]]+1;
		sum[p]=sum[ls[p]]+sum[rs[p]]+val[p];
	}
	void pushdown(int p){ // 下传翻转标记
		if(!rev[p])return;
		swap(ls[p],rs[p]);
		if(ls[p])rev[ls[p]]^=1;
		if(rs[p])rev[rs[p]]^=1;
		rev[p]=0;
	}
	void splitv(int p,ll v,int&x,int&y){ // 值不超过 v 的给 x
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(val[p]<=v){
			x=p;
			splitv(rs[p],v,rs[p],y);
		}else{
			y=p;
			splitv(ls[p],v,x,ls[p]);
		}
		pushup(p);
	}
	void split(int p,int k,int&x,int&y){ // 前 k 个给 x
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(siz[ls[p]]<k){
			x=p;
			split(rs[p],k-siz[ls[p]]-1,rs[p],y);
		}else{
			y=p;
			split(ls[p],k,x,ls[p]);
		}
		pushup(p);
	}
	int merge(int x,int y){ // x 的元素都在 y 前面
		if(!x||!y)return x|y;
		if(rnd[x]<rnd[y]){
			pushdown(x);
			rs[x]=merge(rs[x],y);
			pushup(x);
			return x;
		}
		pushdown(y);
		ls[y]=merge(x,ls[y]);
		pushup(y);
		return y;
	}
	// ---- 用法 1: 按值的可重集合 ----
	void insert(ll v){
		int x,y;
		splitv(root,v,x,y);
		root=merge(merge(x,newnode(v)),y);
	}
	void erase(ll v){ // 删一个 v, 没有则不变
		int x,y,z;
		splitv(root,v,x,z);
		splitv(x,v-1,x,y); // y 里全是 v
		y=merge(ls[y],rs[y]); // 删掉 y 的根
		root=merge(merge(x,y),z);
	}
	int getrank(ll v){ // 严格小于 v 的个数 + 1
		int x,y;
		splitv(root,v-1,x,y);
		int r=siz[x]+1;
		root=merge(x,y);
		return r;
	}
	ll kth(int k){ // 第 k 小, k 从 1 开始
		int p=root;
		while(1){
			if(k<=siz[ls[p]]){
				p=ls[p];
			}else if(k==siz[ls[p]]+1){
				return val[p];
			}else{
				k-=siz[ls[p]]+1;
				p=rs[p];
			}
		}
	}
	ll pre(ll v){return kth(getrank(v)-1);} // 小于 v 的最大值
	ll nxt(ll v){return kth(getrank(v+1));} // 大于 v 的最小值
	// ---- 用法 2: 序列, 位置从 1 开始 ----
	void reverse(int l,int r){
		int x,y,z;
		split(root,r,x,z);
		split(x,l-1,x,y); // y 为 [l, r]
		rev[y]^=1;
		root=merge(merge(x,y),z);
	}
	ll rangeSum(int l,int r){
		int x,y,z;
		split(root,r,x,z);
		split(x,l-1,x,y);
		ll s=sum[y];
		root=merge(merge(x,y),z);
		return s;
	}
	void dfs(int p,vector<ll>&o){ // 中序遍历
		if(!p)return;
		pushdown(p);
		dfs(ls[p],o);
		o.push_back(val[p]);
		dfs(rs[p],o);
	}
}tr;
