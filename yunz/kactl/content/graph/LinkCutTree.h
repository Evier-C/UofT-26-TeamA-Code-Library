/**
 * Description: LCT 动态树 (点 $1..n$), 支持连边, 删边, 判连通, 单点
 * 改值, 路径求和. 每条实链用一棵 splay 维护 (中序为深度从小到大),
 * fa[x] 对 splay 根表示虚边指向的父亲. split(x,y) 后 $y$ 为 splay 根,
 * sum[y] 即 $x$ 到 $y$ 路径和. 维护 max/xor 等改 pushup 即可.
 * Usage: for(int i=1;i<=n;i++) val[i]=a[i]; init(n);
 * link(x,y); cut(x,y); // 不合法的操作会被忽略
 * connected(x,y); modify(x,v); // val[x] 改为 v
 * split(x,y); ll s=sum[y]; // 要求 x,y 连通
 * Time: 均摊 O(\log n)
 */
#pragma once

const int N=3e5+5;
int ch[N][2],fa[N],rev[N],st[N];ll val[N],sum[N];
bool nrt(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];}
void pushr(int x){swap(ch[x][0],ch[x][1]),rev[x]^=1;}
void pushdown(int x){
	if(rev[x])pushr(ch[x][0]),pushr(ch[x][1]),rev[x]=0;
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nrt(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;
	fa[y]=x,fa[x]=z,pushup(y);
}
void splay(int x){
	int y=x,tp=0;st[++tp]=y;
	while(nrt(y))st[++tp]=y=fa[y];
	while(tp)pushdown(st[tp--]);
	while(nrt(x)){
		y=fa[x];int z=fa[y];
		if(nrt(y))rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int y=0;x;y=x,x=fa[x])splay(x),ch[x][1]=y,pushup(x);
}
void makert(int x){access(x),splay(x),pushr(x);}
int findrt(int x){
	access(x),splay(x);
	while(ch[x][0])pushdown(x),x=ch[x][0];
	splay(x);return x;
}
void split(int x,int y){makert(x),access(y),splay(y);}
bool connected(int x,int y){return findrt(x)==findrt(y);}
void link(int x,int y){makert(x);if(findrt(y)!=x)fa[x]=y;}
void cut(int x,int y){
	makert(x);
	if(findrt(y)==x&&fa[y]==x&&!ch[y][0])
		fa[y]=ch[x][1]=0,pushup(x);
}
void modify(int x,ll v){splay(x),val[x]=v,pushup(x);}
void init(int n){
	for(int i=1;i<=n;i++)
		ch[i][0]=ch[i][1]=fa[i]=rev[i]=0,sum[i]=val[i];
}
