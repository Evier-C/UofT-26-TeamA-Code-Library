/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: 树链剖分: 把树分解为点不相交的重链和轻边, 使任意叶子到根的路径上
 * 至多有 log(n) 条轻边. 输入邻接表 (若邻接表中没有指向父亲的边, 注释掉 dfsSz
 * 中的 (*) 行), 初值数组 $v$ 和根. VALS\_EDGES 为真表示值存在边上而不是点上.
 * Usage: vector<T> vals(n, {x, x, 1}); HLD<false> h(adj, vals, root);
 * h.modifyPath(u, v, {d}); // 路径上每个点加 d
 * T x = h.queryPath(u, v), y = h.querySubtree(v);
 * Time: O((\log N)^2)
 * Status: tested on https://cses.fi/problemset/result/16580118/
*/
#pragma once

#include "../data-structures/LazySegmentTree.h"

template<bool VALS_EDGES>struct HLD{
    int N,tim=0;
    vector<vi>adj;
    vi par,siz,rt,pos,tail;
    Seg tree=Seg(vector<T>(1,idT));
    HLD(vector<vi>&adj,vector<T>v,int root)
        :N(sz(adj)),adj(adj),par(N,-1),siz(N,1),
          rt(N,root),pos(N),tail(N,-1){
        dfsSz(root);dfsHld(root);
        vector<T>a(N,idT);
        rep(i,0,N)a[pos[i]]=v[i]; // 按 dfs 序放初值
        tree=Seg(a);
    }
	void dfsSz(int v){
		for(int&u:adj[v]){
			adj[u].erase(find(all(adj[u]),v)); // (*)
			par[u]=v;
			dfsSz(u);
			siz[v]+=siz[u];
			if(siz[u]>siz[adj[v][0]])swap(u,adj[v][0]);
		}
	}
    void dfsHld(int v){
        pos[v]=tim++,tail[v]=v;
        for(bool fst=1;int u:adj[v]){
            rt[u]=(u==adj[v][0]?rt[v]:u);
            dfsHld(u);
            if(fst)tail[v]=tail[u];
            fst=0;
        }
    }
	template<class B>void process(int u,int v,B op){
		for(;;v=par[rt[v]]){
			if(pos[u]>pos[v])swap(u,v);
			if(rt[u]==rt[v])break;
			op(pos[rt[v]],pos[v]+1);
		}
		op(pos[u]+VALS_EDGES,pos[v]+1);
	}
    T get(int u){ // 单点修改类似
        return tree.query(pos[u],pos[u]+1);
    }
	void modifyPath(int u,int v,U val){
		process(u,v,[&](int l,int r){tree.update(l,r,val);});
	}
	// 查整条链用 tree.query(pos[rt[v]], pos[tail[v]] + 1)
    T queryPath(int u,int v){ // 按题意修改
        T res=idT; // 单位元
        process(u,v,[&](int l,int r){ // 合并区间答案
                res=f(res,tree.query(l,r));
        });
        return res;
    }
    T querySubtree(int v){ // modifySubtree 类似
        return tree.query(pos[v]+VALS_EDGES,pos[v]+siz[v]);
    }
};
