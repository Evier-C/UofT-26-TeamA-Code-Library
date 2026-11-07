/**
 * Description: 并查集 DSU 和可撤销并查集 RollbackDSU, 点 1..n, 互相独立, 只抄需要的.
 * 可撤销版按大小合并, 不能加路径压缩. 对象要定义在全局.
 * Usage: dsu.init(n); // 普通版, 多组数据重新 init
 * bool ok = dsu.unite(x, y); // 已连通返回 0
 * if (dsu.find(x) == dsu.find(y)) ...; // 是否连通
 * rdsu.init(n); // 可撤销版
 * int t = rdsu.time(); // 记下当前时间
 * rdsu.unite(x, y); rdsu.unite(y, z);
 * int s = rdsu.siz[rdsu.find(x)]; // 集合大小
 * rdsu.rollback(t); // 撤销 t 之后的所有合并
 * RollbackDSU rdsu2; // 第二个对象, 写在全局
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
