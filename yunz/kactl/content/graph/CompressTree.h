/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: 虚树: 给定有根树和点集 S, 加入所有两两的 LCA (至多 $|S|-1$ 个)
 * 并压缩边, 得到包含 S 中所有点的最小子树.
 * 返回 (par, orig\_index) 的列表, 表示一棵以 0 为根的树,
 * 其中 par 是该列表中的下标, 根指向自己.
 * Usage: LCA lca(C, rt); vpi t = compressTree(lca, S);
 * // t[i] = (par, orig) , par 为 t 中的下标 , t[0] 为根
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

typedef vector<pair<int,int>>vpi;
vpi compressTree(LCA&lca,const vi&subset){
	static vi rev;rev.resize(sz(lca.time));
	vi li=subset,&T=lca.time;
	auto cmp=[&](int a,int b){return T[a]<T[b];};
	sort(all(li),cmp);
	int m=sz(li)-1;
	rep(i,0,m){
		int a=li[i],b=li[i+1];
		li.push_back(lca.lca(a,b));
	}
	sort(all(li),cmp);
	li.erase(unique(all(li)),li.end());
	rep(i,0,sz(li))rev[li[i]]=i;
	vpi ret={pii(0,li[0])};
	rep(i,0,sz(li)-1){
		int a=li[i],b=li[i+1];
		ret.emplace_back(rev[lca.lca(a,b)],b);
	}
	return ret;
}
