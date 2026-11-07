/**
 * Description: 离线动态图连通性: 线段树分治 + 可撤销并查集 (点 $1..n$,
 * 时刻 $1..q$). 每条边在一个时刻区间 $[l, r]$ 内存在, 把它挂到线段树
 * 上; solve 时进入结点加边, 离开时撤销. 到叶子 $t$ 时并查集即为时刻
 * $t$ 的图, 默认记录连通块个数 cc, 可在叶子处改成回答任意询问 (如
 * find(x)==find(y)). 第 $i$ 个操作就是时刻 $i$: 边在时刻 $a$ 加入, 时刻
 * $b$ 删除, 则区间为 $[a, b-1]$; 到最后都没删的边区间为 $[a, q]$.
 * Usage: init(n,q); // q 个时刻, 多组数据重新调用
 * map<pair<int,int>,int> st; // 边 (u<v) 的加入时刻
 * add(1,1,q,l,r,u,v); // 边 (u,v) 在时刻 [l,r] 存在
 * solve(1,1,q); // ans[t] 为时刻 t 的连通块数
 * Time: O(m \log q \log n)
 */
#pragma once

const int N=1e5+5,T=1e5+5; // N 点数, T 时刻数
int fa[N],siz[N],stk[N],tp,cc,ans[T];
vector<pair<int,int>>e[T<<2];
// 按大小合并, 不路径压缩 (才能撤销)
int find(int x){while(x!=fa[x])x=fa[x];return x;}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(siz[x]<siz[y])swap(x,y);
	fa[y]=x,siz[x]+=siz[y],stk[++tp]=y,cc--;
}
void undo(int t){ // 撤销到栈大小为 t
	while(tp>t){
		int y=stk[tp--];
		siz[fa[y]]-=siz[y],fa[y]=y,cc++;
	}
}
void init(int n,int q){
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	for(int i=0;i<=q*4;i++)e[i].clear();
	cc=n,tp=0;
}
void add(int p,int l,int r,int ql,int qr,int u,int v){
	if(ql>qr)return;
	if(ql<=l&&r<=qr){e[p].push_back({u,v});return;}
	int mid=(l+r)/2;
	if(ql<=mid)add(p*2,l,mid,ql,qr,u,v);
	if(qr>mid)add(p*2+1,mid+1,r,ql,qr,u,v);
}
void solve(int p,int l,int r){
	int t=tp;
	for(auto[u,v]:e[p])merge(u,v);
	if(l==r)ans[l]=cc; // 在这里回答时刻 l 的询问
	else{
		int mid=(l+r)/2;
		solve(p*2,l,mid),solve(p*2+1,mid+1,r);
	}
	undo(t);
}
