/**
 * Description: 输出 $s$-$t$ 最小割方案, 配合 Dinic.h 的对象使用.
 * 最小割 = 最大流. 对某个 Dinic 对象 G 跑完 G.dinic(s,t) 后,
 * 最后一次 bfs 失败, 此时 G.dep[v] 非 0 的点就是残量网络中从 $s$
 * 能到达的点, 构成 $S$ 侧, 其余点为 $T$ 侧.
 * 割边为从 $S$ 侧指向 $T$ 侧的原边, 它们都满流.
 * 函数: minCut(G) 返回 G 中所有割边的编号 (即 add 的返回值, 正向边).
 * 对割边 $e$: 起点 $\text{G.to}[e \oplus 1]$, 终点 $\text{G.to}[e]$,
 * 原容量 $\text{G.cap}[e \oplus 1]$, 这些容量之和等于最大流.
 * 若要割点 (每个点拆成入点, 出点, 中间连容量 1 的边) 同理读割边.
 * 注意: 必须在 dinic 之后, 下一次 init 之前调用.
 * Usage: D.init(n); // D 为 Dinic.h 中的全局对象
 * for(int i=1;i<=m;i++) D.add(u[i],v[i],c[i]);
 * ll f=D.dinic(s,t); // 最小割的值
 * vector<int> cut=minCut(D);
 * for(int e:cut) // 输出割边 u v
 *   cout<<D.to[e^1]<<' '<<D.to[e]<<endl;
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
