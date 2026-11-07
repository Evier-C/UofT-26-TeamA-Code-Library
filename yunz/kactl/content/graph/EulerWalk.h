/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: 无向/有向图的欧拉路径/回路. 输入为 (终点, 全局边编号)
 * 的邻接表, 无向图中正反两条边编号相同. 返回欧拉路径/回路上的点序列
 * (从 src 开始; 回路时首尾都是 src), 不存在时返回空.
 * 若要得到边编号, 在 s 和 ret 中额外存 .second.
 * Usage: vector<vector<pii>> gr(n); gr[a].push_back({b, i});
 * gr[b].push_back({a, i}); // 仅无向图需要
 * vi path = eulerWalk(gr, nedges, src); // 空表示不存在
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vi eulerWalk(vector<vector<pii>>&gr,int nedges,int src=0){
	int n=sz(gr);
	vi D(n),its(n),eu(nedges),ret,s={src};
	D[src]++; // 允许欧拉路径 而不只是回路
	while(!s.empty()){
		int x=s.back(),y,e,&it=its[x],end=sz(gr[x]);
		if(it==end){ret.push_back(x);s.pop_back();continue;}
		tie(y,e)=gr[x][it++];
		if(!eu[e]){
			D[x]--,D[y]++;
			eu[e]=1;s.push_back(y);
		}}
	for(int x:D)if(x<0||sz(ret)!=nedges+1)return {};
	return {ret.rbegin(),ret.rend()};
}
