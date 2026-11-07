/**
 * Description: FHQ treap (split/merge, 无旋转), 节点 0 表示空. 两种用法:
 * (1) 按值有序的可重集合: insert, erase, getrank, kth, pre, nxt;
 * (2) 按位置的序列: 按大小 split, 区间翻转, 区间和.
 * 两种用法不要混在同一棵树上. sum 和 rev 只给序列用.
 * kth, pre, nxt 要保证答案存在. N 为插入总次数, 删掉的节点不回收.
 * Usage: tot = root = 0; // 多组数据清空
 * insert(v); erase(v); getrank(v); kth(k); pre(v); nxt(v);
 * // 建序列: 依次加到末尾
 * for (int i = 1; i <= n; i++)
 *   root = merge(root, newnode(a[i]));
 * reverse(l, r); rangeSum(l, r); // 位置从 1 开始
 * vector<ll> o; dfs(root, o); // 中序遍历得到当前序列
 * Time: 每次操作期望 O(\log N)
 */
#pragma once

const int N=2e5+5; // 插入总次数
int ls[N],rs[N],siz[N],tot,root;
unsigned rnd[N];ll val[N],sum[N];bool rev[N];
mt19937 rng(12345);
int newnode(ll v){
	int p=++tot;
	ls[p]=rs[p]=0,siz[p]=1,rev[p]=0;
	rnd[p]=rng(),val[p]=sum[p]=v;
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
	if(!p){x=y=0;return;}
	pushdown(p);
	if(val[p]<=v)x=p,splitv(rs[p],v,rs[p],y);
	else y=p,splitv(ls[p],v,x,ls[p]);
	pushup(p);
}
void split(int p,int k,int&x,int&y){ // 前 k 个给 x
	if(!p){x=y=0;return;}
	pushdown(p);
	if(siz[ls[p]]<k)x=p,split(rs[p],k-siz[ls[p]]-1,rs[p],y);
	else y=p,split(ls[p],k,x,ls[p]);
	pushup(p);
}
int merge(int x,int y){ // x 的元素都在 y 前面
	if(!x||!y)return x|y;
	if(rnd[x]<rnd[y]){
		pushdown(x),rs[x]=merge(rs[x],y),pushup(x);
		return x;
	}
	pushdown(y),ls[y]=merge(x,ls[y]),pushup(y);
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
	splitv(root,v,x,z),splitv(x,v-1,x,y);
	y=merge(ls[y],rs[y]);
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
		if(k<=siz[ls[p]])p=ls[p];
		else if(k==siz[ls[p]]+1)return val[p];
		else k-=siz[ls[p]]+1,p=rs[p];
	}
}
ll pre(ll v){return kth(getrank(v)-1);} // 小于 v 的最大值
ll nxt(ll v){return kth(getrank(v+1));} // 大于 v 的最小值
// ---- 用法 2: 序列, 位置从 1 开始 ----
void reverse(int l,int r){
	int x,y,z;
	split(root,r,x,z),split(x,l-1,x,y);
	rev[y]^=1;
	root=merge(merge(x,y),z);
}
ll rangeSum(int l,int r){
	int x,y,z;
	split(root,r,x,z),split(x,l-1,x,y);
	ll s=sum[y];
	root=merge(merge(x,y),z);
	return s;
}
void dfs(int p,vector<ll>&o){ // 中序遍历
	if(!p)return;
	pushdown(p),dfs(ls[p],o);
	o.push_back(val[p]),dfs(rs[p],o);
}
