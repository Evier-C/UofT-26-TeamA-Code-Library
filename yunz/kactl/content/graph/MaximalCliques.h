/**
 * Author: Simon Lindholm
 * Date: 2018-07-18
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * Description: 对图中每个极大团调用回调 (图以对称的 bitset 邻接矩阵给出,
 * 不允许自环). 回调的参数是表示该极大团的 bitset.
 * Usage: vector<B> eds(n); // eds[i][j] = 1 表示有边
 * cliques(eds, [\&](B r) { ... }); // r 为一个极大团
 * Time: O(3^{n/3}), 稀疏图上快得多
 * Status: stress-tested
 */
#pragma once
/// 可能的优化 : 在最顶层递归忽略 'cands' , 按度数递增的
/// 顺序遍历点 , 删点时度数随之减小 . 有了 MaximumClique
/// 后基本不需要

typedef bitset<128>B;
template<class F>
void cliques(vector<B>&eds,F f,B P=~B(),B X={},B R={}){
	if(!P.any()){if(!X.any())f(R);return;}
	auto q=(P|X)._Find_first();
	auto cands=P&~eds[q];
	rep(i,0,sz(eds))if(cands[i]){
		R[i]=1;
		cliques(eds,f,P&eds[i],X&eds[i],R);
		R[i]=P[i]=0;X[i]=1;
	}
}
