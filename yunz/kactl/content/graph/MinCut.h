/**
 * Description: 输出 $s$-$t$ 最小割方案 (配合 Dinic). 跑完 dinic(s,t) 后,
 * 最后一次 bfs 失败, dep[v] 非 0 的点即残量网络中从 $s$ 能到达的点,
 * 构成最小割的 $S$ 侧, 其余点为 $T$ 侧. 割边为从 $S$ 侧指向 $T$ 侧的原边,
 * 它们都满流, 原容量为 $\text{cap}[e \oplus 1]$, 容量和等于最大流.
 * Usage: ll f=dinic(s,t); // 先跑最大流
 * vector<int> cut=minCut(); // 割边编号, 即 add 的返回值
 * for(int e:cut) cout<<to[e^1]<<' '<<to[e]<<endl; // 割边 u v
 * for(int v=1;v<=n;v++) if(dep[v]) ...; // v 在 S 侧
 * Time: O(E)
 */
#pragma once

#include "Dinic.h"

vector<int>minCut(){ // 跑完 dinic 后调用
	vector<int>res;
	for(int e=2;e<=cnt;e+=2) // 只看正向边
		if(dep[to[e^1]]&&!dep[to[e]])res.push_back(e);
	return res;
}
