/**
 * Description: 离线动态图连通性 (线段树分治 + 可撤销并查集), 点 $1..n$,
 * 时刻 $1..q$. 支持加边, 删边, 询问某时刻的连通块个数 (或两点是否
 * 连通), 全部操作先读入. 结构体 DynConn, 全局对象 DC.
 * 做法: 每条边在一个时刻区间 $[l, r]$ 内存在, 用 add 挂到线段树上
 * $O(\log q)$ 个结点; solve 时进入结点加边, 离开时撤销, 到叶子 $t$ 时
 * 并查集恰好是时刻 $t$ 的图. ans[t] 为时刻 $t$ 的连通块个数 cc; 在
 * solve 的叶子处可以改成回答任意询问 (如 find(x)==find(y)).
 * 时刻: 第 $i$ 个操作就是时刻 $i$. 边在时刻 $a$ 加入, 时刻 $b$ 删除,
 * 区间为 $[a, b-1]$; 到最后都没删的边区间为 $[a, q]$. 同一条边先把
 * $u, v$ 排成 $u<v$ 再用 map 记加入时刻.
 * 并查集按大小合并, 不路径压缩 (才能撤销). N 点数, T 时刻数上限.
 * 对象很大, 必须是全局 (或 static) 变量; 第二个: 全局写 DynConn DC2;
 * Usage: DC.init(n,q); // q 个时刻, 多组数据每组调用
 * map<pair<int,int>,int> st; // 边的加入时刻
 * for(int i=1;i<=q;i++){
 *   cin>>op>>u>>v;
 *   if(u>v) swap(u,v);
 *   if(op==1) st[{u,v}]=i; // 加边
 *   if(op==2){ // 删边
 *     DC.add(1,1,q,st[{u,v}],i-1,u,v);
 *     st.erase({u,v});
 *   }
 * }
 * for(auto [e,t]:st) DC.add(1,1,q,t,q,e.first,e.second);
 * DC.solve(1,1,q); // DC.ans[t] 为时刻 t 的连通块数
 * Time: O(m \log q \log n)
 */
#pragma once

struct DynConn{
	static const int N=1e5+5,T=1e5+5; // N 点数, T 时刻数
	int fa[N],siz[N],stk[N],tp,cc,ans[T];
	vector<pair<int,int>>e[T<<2]; // 线段树结点上的边
	int find(int x){
		while(x!=fa[x])x=fa[x];
		return x;
	}
	void merge(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return;
		if(siz[x]<siz[y])swap(x,y);
		fa[y]=x;
		siz[x]+=siz[y];
		stk[++tp]=y; // 记录被挂上去的根
		cc--;
	}
	void undo(int t){ // 撤销到栈大小为 t
		while(tp>t){
			int y=stk[tp--];
			siz[fa[y]]-=siz[y];
			fa[y]=y;
			cc++;
		}
	}
	void init(int n,int q){
		for(int i=1;i<=n;i++){
			fa[i]=i;
			siz[i]=1;
		}
		for(int i=0;i<=q*4;i++)e[i].clear();
		cc=n;
		tp=0;
	}
	// 边 (u,v) 在时刻 [ql,qr] 存在
	void add(int p,int l,int r,int ql,int qr,int u,int v){
		if(ql>qr)return;
		if(ql<=l&&r<=qr){
			e[p].push_back({u,v});
			return;
		}
		int mid=(l+r)/2;
		if(ql<=mid)add(p*2,l,mid,ql,qr,u,v);
		if(qr>mid)add(p*2+1,mid+1,r,ql,qr,u,v);
	}
	void solve(int p,int l,int r){
		int t=tp;
		for(auto[u,v]:e[p])merge(u,v);
		if(l==r){
			ans[l]=cc; // 在这里回答时刻 l 的询问
		}else{
			int mid=(l+r)/2;
			solve(p*2,l,mid);
			solve(p*2+1,mid+1,r);
		}
		undo(t);
	}
}DC;
