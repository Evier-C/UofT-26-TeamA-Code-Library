/**
 * Description: 并查集, 点 1..n. 上半: 普通并查集, 路径压缩.
 * 下半: 可撤销并查集, 按大小合并, 不压缩路径. 每次成功合并压栈一次,
 * rollback(t) 撤销到 time() 等于 t 时的状态. 两者互相独立, 只抄需要的.
 * Usage: init(n); unite(x, y); find(x) == find(y); // 普通
 * initR(n); uniteR(x, y); findR(x); siz[findR(x)]; // 可撤销
 * int t = time(); uniteR(x, y); ...; rollback(t);
 * Time: 普通 均摊 $O(\log N)$, 实际接近 $O(1)$; 可撤销 $O(\log N)$
 */
#pragma once

const int N=2e5+5;
int fa[N];
void init(int n){for(int i=1;i<=n;i++)fa[i]=i;}
int find(int x){ // 路径压缩: 减半写法, 不递归, 不怕爆栈
	while(fa[x]!=x)x=fa[x]=fa[fa[x]];
	return x;
}
bool unite(int x,int y){ // 已在同一集合返回 0
	x=find(x),y=find(y);
	if(x==y)return 0;
	fa[x]=y;return 1;
}

int pa[N],siz[N],stk[N],top; // stk: 被挂到别人下面的根
void initR(int n){
	top=0;
	for(int i=1;i<=n;i++)pa[i]=i,siz[i]=1;
}
int findR(int x){while(pa[x]!=x)x=pa[x];return x;}
bool uniteR(int x,int y){
	x=findR(x),y=findR(y);
	if(x==y)return 0;
	if(siz[x]>siz[y])swap(x,y); // 小的挂到大的下面
	pa[x]=y,siz[y]+=siz[x],stk[++top]=x;
	return 1;
}
int time(){return top;}
void rollback(int t){ // 撤销到 time() 等于 t 时
	while(top>t){
		int x=stk[top--];
		siz[pa[x]]-=siz[x],pa[x]=x;
	}
}
