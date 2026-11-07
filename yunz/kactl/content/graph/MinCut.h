/**
 * Description: 输出 $s$-$t$ 最小割方案, 配合 Dinic 对象使用.
 * 必须在 dinic 之后, 下一次 init 之前调用.
 * Usage: D.init(n); // D 为 Dinic.h 中的全局对象
 * for(int i=1;i<=m;i++) D.add(u[i],v[i],c[i]);
 * ll f=D.dinic(s,t); // 最小割的值
 * vector<int> cut=minCut(D); // 割边编号, 即 add 的返回值
 * for(int e:cut) // 割边 u v 及其容量, 容量和等于 f
 *   cout<<D.to[e^1]<<' '<<D.to[e]<<' '<<D.cap[e^1]<<endl;
 * for(int v=1;v<=n;v++) if(D.dep[v]) cout<<v<<' '; // S 侧
 * Time: O(E)
 */
#pragma once

#include "Dinic.h"

vector<int>minCut(Dinic&G){ // 跑完 G.dinic 后调用
	vector<int>res;
	for(int e=2;e<=G.cnt;e+=2){ // 只看正向边
		if(G.dep[G.to[e^1]]&&!G.dep[G.to[e]])res.push_back(e);
	}
	return res;
}
