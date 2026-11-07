/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: 预处理树上 2 的幂次跳跃表 (倍增),
 * 支持快速向上跳和求 LCA.
 * 要求根的父亲是它自己.
 * Usage: vi P(n); // P[v] 为父亲 , P[root] = root
 * vector<vi> tbl = treeJump(P); int u = jmp(tbl, v, k);
 * int w = lca(tbl, depth, a, b); // depth 为深度数组 vi
 * Time: 预处理 $O(N \log N)$, 查询 $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<vi>treeJump(vi&P){
	int on=1,d=1;
	while(on<sz(P))on*=2,d++;
	vector<vi>jmp(d,P);
	rep(i,1,d)rep(j,0,sz(P))
		jmp[i][j]=jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>&tbl,int nod,int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i))nod=tbl[i][nod];
	return nod;
}

int lca(vector<vi>&tbl,vi&depth,int a,int b){
	if(depth[a]<depth[b])swap(a,b);
	a=jmp(tbl,a,depth[a]-depth[b]);
	if(a==b)return a;
	for(int i=sz(tbl);i--;){
		int c=tbl[i][a],d=tbl[i][b];
		if(c!=d)a=c,b=d;
	}
	return tbl[0][a];
}
