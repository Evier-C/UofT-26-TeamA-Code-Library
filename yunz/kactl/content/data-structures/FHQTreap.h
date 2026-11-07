/**
 * Description: FHQ treap: 无旋平衡树, 只靠 split 和 merge, 节点 0 表示空.
 * 两种用法, 不要混在同一棵树上:
 * 用法 1, 按值有序的可重集合, 根为 root:
 * insert(v) 插入一个 v; erase(v) 删除一个 v, 没有则不变;
 * getrank(v) 返回严格小于 v 的个数加 1; kth(k) 返回第 k 小, k 从 1 开始;
 * pre(v) 返回小于 v 的最大值; nxt(v) 返回大于 v 的最小值.
 * 用法 2, 按位置的序列 a[1..n], 支持区间翻转和区间和:
 * 用 root = merge(root, newnode(x)) 依次加到末尾建树;
 * reverse(l, r) 翻转 a[l..r]; rangeSum(l, r) 返回 a[l..r] 的和;
 * dfs(root, o) 按中序把当前序列放进 vector o.
 * 要加别的区间操作: 仿照 reverse, 先 split 出 [l, r] 这棵树 y, 改 y 再 merge 回去.
 * 注意: kth, pre, nxt 要保证答案存在; N 为插入总次数, 删掉的节点不回收;
 * 多组数据令 tot = root = 0.
 * Usage: tot = root = 0; // 多组数据清空
 * // 用法 1
 * insert(5); insert(3); insert(5); erase(5);
 * int r = getrank(5); // 2
 * ll v = kth(1), p = pre(5), q = nxt(3); // 3, 3, 5
 * // 用法 2
 * for (int i = 1; i <= n; i++)
 *   root = merge(root, newnode(a[i]));
 * reverse(l, r); ll s = rangeSum(l, r);
 * vector<ll> o; dfs(root, o); // o 为当前序列
 * Time: 每次操作期望 O(\log N)
 */
#pragma once

const int N=2e5+5; // 插入总次数
int ls[N],rs[N],siz[N],tot,root;
unsigned rnd[N];
ll val[N],sum[N];
bool rev[N];
mt19937 rng(12345);
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
