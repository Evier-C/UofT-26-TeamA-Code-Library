/**
 * Description: 输出 $s$-$t$ 最小割方案, 配合 Dinic.h 使用.
 * 最小割 = 最大流. 跑完 dinic(s,t) 后最后一次 bfs 失败,
 * 此时 dep[v] 非 0 的点就是残量网络中从 $s$ 能到达的点, 构成 $S$ 侧,
 * 其余点为 $T$ 侧. 割边为从 $S$ 侧指向 $T$ 侧的原边, 它们都满流.
 * 函数: minCut() 返回所有割边的编号 (即 add 的返回值, 正向边).
 * 对割边 $e$: 起点 $\text{to}[e \oplus 1]$, 终点 $\text{to}[e]$, 原容量 $\text{cap}[e \oplus 1]$,
 * 这些容量之和等于最大流.
 * 若要割点 (每个点拆成入点, 出点, 中间连容量 1 的边) 同理读割边.
 * 注意: 必须在 dinic 之后, 下一次 init 之前调用.
 * Usage: init(n);
 * for(int i=1;i<=m;i++) add(u[i],v[i],c[i]);
 * ll f=dinic(s,t); // 最小割的值
 * vector<int> cut=minCut();
 * for(int e:cut) cout<<to[e^1]<<' '<<to[e]<<endl; // 割边 u v
 * for(int v=1;v<=n;v++) if(dep[v]) cout<<v<<' '; // S 侧的点
 * Time: O(E)
 */
#pragma once

#include "Dinic.h"

vector<int>minCut(){ // 跑完 dinic 后调用
	vector<int>res;
	for(int e=2;e<=cnt;e+=2){ // 只看正向边
		if(dep[to[e^1]]&&!dep[to[e]])res.push_back(e);
	}
	return res;
}
