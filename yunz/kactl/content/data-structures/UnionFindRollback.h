/**
 * Description: 并查集, 点 1..n, 两个结构体互相独立, 只抄需要的.
 * 普通并查集 DSU, 全局对象 dsu: init(n) 初始化; find(x) 返回 x 所在集合的根;
 * unite(x, y) 合并两个集合, 已在同一集合返回 0, 否则返回 1.
 * 可撤销并查集 RollbackDSU, 全局对象 rdsu: 按大小合并, 不压缩路径,
 * 所以 find 是 $O(\log n)$. init(n) 初始化; find(x) 返回根;
 * siz[find(x)] 为 x 所在集合大小; unite(x, y) 同上, 每次成功合并压栈一次;
 * time() 返回当前栈大小; rollback(t) 撤销到 time() 等于 t 时的状态,
 * 即撤销 t 之后的所有合并.
 * 常用于线段树分治, 离线动态连通性, 按顺序试加边再撤销.
 * 注意: 撤销版不能路径压缩; 多组数据重新 init 即可; 对象要定义在全局,
 * 要多个就在全局再写 DSU dsu2; 或 RollbackDSU rdsu2;
 * Usage: dsu.init(n); // 普通版
 * dsu.unite(x, y);
 * if (dsu.find(x) == dsu.find(y)) ...; // 是否连通
 * rdsu.init(n); // 可撤销版
 * int t = rdsu.time(); // 记下当前时间
 * rdsu.unite(x, y); rdsu.unite(y, z);
 * int s = rdsu.siz[rdsu.find(x)]; // 集合大小
 * rdsu.rollback(t); // 撤销上面两次合并
 * Time: 普通 均摊 $O(\log N)$, 实际接近 $O(1)$; 可撤销 $O(\log N)$
 */
#pragma once

struct DSU{
	static const int N=2e5+5;
	int fa[N];
	void init(int n){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	int find(int x){ // 路径压缩: 减半写法, 不递归, 不怕爆栈
		while(fa[x]!=x){
			fa[x]=fa[fa[x]];
			x=fa[x];
		}
		return x;
	}
	bool unite(int x,int y){ // 已在同一集合返回 0
		x=find(x);
		y=find(y);
		if(x==y)return 0;
		fa[x]=y;
		return 1;
	}
}dsu;

struct RollbackDSU{
	static const int N=2e5+5;
	int pa[N],siz[N];
	int stk[N],top; // stk: 被挂到别人下面的根
	void init(int n){
		top=0;
		for(int i=1;i<=n;i++){
			pa[i]=i;
			siz[i]=1;
		}
	}
	int find(int x){
		while(pa[x]!=x)x=pa[x];
		return x;
	}
	bool unite(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return 0;
		if(siz[x]>siz[y])swap(x,y); // 小的挂到大的下面
		pa[x]=y;
		siz[y]+=siz[x];
		stk[++top]=x;
		return 1;
	}
	int time(){return top;}
	void rollback(int t){ // 撤销到 time() 等于 t 时
		while(top>t){
			int x=stk[top];
			top--;
			siz[pa[x]]-=siz[x];
			pa[x]=x;
		}
	}
}rdsu;
