/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: 拓扑排序. 输入有向图的邻接表.
 * 输出一个顶点序列, 使所有边都从左指向右.
 * 若有环, 返回序列的长度小于 $n$: 从环出发可达的点都不会出现.
 * Usage: vector<vi> gr(n); gr[a].push_back(b); // 边 a 到 b
 * vi ord = topoSort(gr); // sz(ord) < n 表示有环
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vi topoSort(const vector<vi>&gr){
	vi indeg(sz(gr)),q;
	for(auto&li:gr)for(int x:li)indeg[x]++;
	rep(i,0,sz(gr))if(indeg[i]==0)q.push_back(i);
	rep(j,0,sz(q))for(int x:gr[q[j]])
		if(--indeg[x]==0)q.push_back(x);
	return q;
}
