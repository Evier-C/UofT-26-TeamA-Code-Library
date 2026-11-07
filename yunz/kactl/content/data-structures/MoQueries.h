/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: 莫队: 回答区间或树上路径询问, 在端点处加入/删除点, 从一个询问移到下一个.
 * 若值在树边上, 把 \texttt{step} 改为加入/删除边 $(a, c)$, 并去掉开头的 \texttt{add} 调用 (但保留 \texttt{in}).
 * Usage: vi ans = mo(Q); // Q 为 vector<pii>, 区间 [L, R)
 * vi ans2 = moTree(P, ed, root); // P[i] = {u, v}, ed 为邻接表
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

void add(int ind,int end){...} // 加 a[ind] (end 为 0/1)
void del(int ind,int end){...} // 删除 a[ind]
int calc(){...} // 计算当前答案

vi mo(vector<pii>Q){
	int L=1,R=1,blk=350; // ~N/sqrt(Q)
	vi s(sz(Q)),res=s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s),0);
	sort(all(s),[&](int s,int t){return K(Q[s])<K(Q[t]);});
    for(int qi:s){
        auto[x,y]=Q[qi];
        while(L>x)add(--L,0);
        while(R<y)add(R++,1);
        while(L<x)del(L++,0);
        while(R>y)del(--R,1);
        res[qi]=calc();
    }
	return res; // Q 用左闭右开区间 [L, R)
}

vi moTree(vector<array<int,2>>Q,vector<vi>&ed,int root=0){
	int N=sz(ed),pos[2]={root,root},blk=126; // ~N/sqrt(Q)
	vi s(sz(Q)),res=s,I(N),L(N),R(N),in(N),par(N);
	add(root,0),in[root]=1;
	auto dfs=[&](int x,int p,int dep,auto&f)->void{
		par[x]=p;
		L[x]=N;
		if(dep)I[x]=N++;
		for(int y:ed[x])if(y!=p)f(y,x,!dep,f);
		if(!dep)I[x]=N++;
		R[x]=N;
	};
	dfs(root,-1,0,dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
	iota(all(s),0);
	sort(all(s),[&](int s,int t){return K(Q[s])<K(Q[t]);});
	for(int qi:s)rep(end,0,2){
		int&a=pos[end],b=Q[qi][end],i=0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else{add(c,end);in[c]=1;}a=c;}
		while(!(L[b]<=L[a]&&R[a]<=R[b]))
			I[i++]=b,b=par[b];
		while(a!=b)step(par[a]);
		while(i--)step(I[i]);
		if(end)res[qi]=calc();
	}
	return res; // Q 用闭区间 [L, R]
}
