/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: 求有向图的强连通分量. 若 $u, v$ 在同一分量中,
 * 则 $u$ 可达 $v$ 且 $v$ 可达 $u$.
 * Usage: scc(graph, [\&](vi\& v) { ... }); // 按逆拓扑序访问各分量
 * comp[i] 为点 i 所在分量的编号 ; 分量只会连向
 * 编号更小的分量 . ncomps 为分量个数
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vi val,comp,z,cont;
int Time,ncomps;
template<class G,class F>int dfs(int j,G&g,F&f){
	int low=val[j]=++Time,x;z.push_back(j);
	for(auto e:g[j])if(comp[e]<0)
		low=min(low,val[e]?:dfs(e,g,f));

	if(low==val[j]){
		do{
			x=z.back();z.pop_back();
			comp[x]=ncomps;
			cont.push_back(x);
		}while(x!=j);
		f(cont);cont.clear();
		ncomps++;
	}
	return val[j]=low;
}
template<class G,class F>void scc(G&g,F f){
	int n=sz(g);
	val.assign(n,0);comp.assign(n,-1);
	Time=ncomps=0;
	rep(i,0,n)if(comp[i]<0)dfs(i,g,f);
}
