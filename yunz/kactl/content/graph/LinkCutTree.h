/**
 * Description: LCT 动态树, 维护森林的连边, 删边, 判连通, 单点改值,
 * 路径求和. 维护 max/xor: 改 pushup. 非递归. 对象必须是全局变量.
 * Usage: for(int i=1;i<=n;i++) cin>>L.val[i];
 * L.init(n); // 多组数据每组调用 (先填 val)
 * L.link(x,y); // 加边, 已连通则忽略
 * L.cut(x,y); // 删边, 没有这条边则忽略
 * int r=L.findrt(x); // x 所在树的根
 * L.makert(x); // 换根为 x
 * if(L.connected(x,y)){
 *   L.split(x,y);
 *   ll s=L.sum[y]; // 路径 x 到 y 的点权和
 * }
 * L.modify(x,v); // val[x] 改为 v
 * LCT L2; // 第二个对象 (全局)
 * Time: 均摊 O(\log n)
 */
#pragma once

struct LCT{
	static const int N=3e5+5;
	int ch[N][2],fa[N],rev[N],st[N];
	ll val[N],sum[N];
	// x 不是所在 splay 的根
	bool nrt(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
	void pushup(int x){
		sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];
	}
	void pushr(int x){ // 翻转 x 的子树
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	void pushdown(int x){
		if(rev[x]){
			if(ch[x][0])pushr(ch[x][0]);
			if(ch[x][1])pushr(ch[x][1]);
			rev[x]=0;
		}
	}
	void rotate(int x){
		int y=fa[x],z=fa[y];
		int k=ch[y][1]==x,w=ch[x][!k];
		if(nrt(y))ch[z][ch[z][1]==y]=x;
		ch[x][!k]=y;
		ch[y][k]=w;
		if(w)fa[w]=y;
		fa[y]=x;
		fa[x]=z;
		pushup(y);
	}
	void splay(int x){
		// 先从上到下 pushdown
		int y=x,tp=0;
		st[++tp]=y;
		while(nrt(y)){
			y=fa[y];
			st[++tp]=y;
		}
		while(tp)pushdown(st[tp--]);
		while(nrt(x)){
			y=fa[x];
			int z=fa[y];
			if(nrt(y)){
				if((ch[y][0]==x)^(ch[z][0]==y))rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
		pushup(x);
	}
	void access(int x){ // 打通根到 x 的实链
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
			ch[x][1]=y;
			pushup(x);
		}
	}
	void makert(int x){
		access(x);
		splay(x);
		pushr(x);
	}
	int findrt(int x){
		access(x);
		splay(x);
		while(ch[x][0]){
			pushdown(x);
			x=ch[x][0];
		}
		splay(x);
		return x;
	}
	void split(int x,int y){
		makert(x);
		access(y);
		splay(y);
	}
	bool connected(int x,int y){return findrt(x)==findrt(y);}
	void link(int x,int y){
		makert(x);
		if(findrt(y)!=x)fa[x]=y;
	}
	void cut(int x,int y){
		makert(x);
		if(findrt(y)==x&&fa[y]==x&&!ch[y][0]){
			fa[y]=0;
			ch[x][1]=0;
			pushup(x);
		}
	}
	void modify(int x,ll v){
		splay(x);
		val[x]=v;
		pushup(x);
	}
	void init(int n){
		for(int i=1;i<=n;i++){
			ch[i][0]=ch[i][1]=fa[i]=rev[i]=0;
			sum[i]=val[i];
		}
	}
}L;
