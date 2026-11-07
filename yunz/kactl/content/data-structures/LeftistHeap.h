/**
 * Description: 左偏树: 可合并的小根堆, 节点即元素, 值相等时编号小的在上.
 * N 为节点总数; 对象要定义在全局. 改大根堆就把 merge 的比较反过来.
 * Usage: lh.init(); // 清空, 每组数据调用
 * // 第 i 个元素就是节点 i
 * for (int i = 1; i <= n; i++) lh.newnode(a[i]);
 * lh.join(x, y); // 合并 x, y 所在的堆, 已删或同堆则不动
 * if (lh.del[x]) cout << -1 << endl; // x 已被删
 * else {
 *   cout << lh.top(x) << endl; // x 所在堆的最小值
 *   lh.pop(x); // 删掉它
 * }
 * int r = lh.find(x); // x 所在堆的根
 * int u = lh.merge(r1, r2); // 直接合并两个根, 返回新根
 * Time: 合并, 删除 $O(\log N)$; find 均摊 $O(\log N)$
 */
#pragma once

struct LeftistHeap{
	static const int N=2e5+5;
	int ls[N],rs[N],d[N],fa[N],tot;
	ll val[N];
	bool del[N];
	void init(){
		tot=0;
		d[0]=-1;
	}
	int newnode(ll v){
		int p=++tot;
		val[p]=v;
		ls[p]=0;
		rs[p]=0;
		d[p]=0;
		fa[p]=p;
		del[p]=0;
		return p;
	}
	int merge(int x,int y){ // 返回新根
		if(!x||!y)return x|y;
		// 让 x 是较小的根, 相等时编号小的在上
		if(val[x]>val[y]||(val[x]==val[y]&&x>y))swap(x,y);
		rs[x]=merge(rs[x],y);
		if(d[ls[x]]<d[rs[x]])swap(ls[x],rs[x]);
		d[x]=d[rs[x]]+1;
		return x;
	}
	int find(int x){ // x 所在堆的根, 路径减半
		while(fa[x]!=x){
			fa[x]=fa[fa[x]];
			x=fa[x];
		}
		return x;
	}
	void join(int x,int y){
		if(del[x]||del[y])return;
		x=find(x);
		y=find(y);
		if(x==y)return;
		int r=merge(x,y);
		fa[x]=r;
		fa[y]=r;
	}
	ll top(int x){return val[find(x)];}
	void pop(int x){
		int r=find(x);
		del[r]=1;
		int nr=merge(ls[r],rs[r]);
		fa[r]=nr; // 指向 r 的点改为找到 nr
		if(nr)fa[nr]=nr;
	}
}lh;
