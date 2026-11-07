/**
 * Description: 左偏树 LeftistHeap, 全局对象 lh: 可合并的小根堆, 两个堆合并
 * $O(\log n)$. 节点即元素, 编号 1..tot, newnode(v) 新建一个只含 v 的堆.
 * dist: d[x] 为 x 到子树里最近的空儿子的边数, 空节点 d[0] = -1, 叶子为 0.
 * 左偏: 每个点都满足 d[ls] 不小于 d[rs], 所以 d[x] = d[rs[x]] + 1, 右链长度
 * 不超过 $\log_2(n + 1)$. merge 只沿两棵树的右链往下走, 故为 $O(\log n)$.
 * merge(x, y): 合并根为 x, y 的两个堆, 返回新根; 值相等时编号小的在上.
 * 删除堆顶 r: 把 ls[r] 和 rs[r] 合并成新堆.
 * 配合并查集: fa 沿着指向自己所在堆的根, 带路径压缩, find(x) 求 x 所在堆的根.
 * 删掉的点 del 标记为 1, 它的 fa 指向新根, 所以堆里其他点仍能找到根.
 * 封装好的操作, 同洛谷 P3377:
 * join(x, y): 若 x, y 都没删且不在同一堆, 合并它们所在的堆;
 * top(x): x 所在堆的最小值, 要求 x 没删;
 * pop(x): 删除 x 所在堆的最小值, 要求 x 没删.
 * 典型用途: 可并堆, 每个点维护子树里的堆再向上合并, 如城池攻占,
 * 可加懒标记; slope trick 里合并拐点集合.
 * 注意: N 为节点总数; 对象要定义在全局; 多组数据调用 init();
 * 换成大根堆把 merge 里的比较反过来.
 * Usage: lh.init(); // 清空, 每组数据调用
 * // 第 i 个元素就是节点 i
 * for (int i = 1; i <= n; i++) lh.newnode(a[i]);
 * lh.join(x, y); // 合并 x 和 y 所在的堆
 * if (lh.del[x]) cout << -1 << endl; // 已被删
 * else {
 *   cout << lh.top(x) << endl; // x 所在堆的最小值
 *   lh.pop(x); // 删掉它
 * }
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
