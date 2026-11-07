/**
 * Description: 二分图最小点覆盖 (König 定理): 选最少的点使每条边
 * 至少有一个端点被选, 大小等于最大匹配数. 补集为最大独立集.
 * 输入: 同 HopcroftKarp.h, 左部 $1..n$, 右部 $1..m$, init(n,m) 后
 * g[u].push\_back(v). 不需要先调用 hk().
 * 函数: cover(A,B) 内部先跑 hk(), 返回最大匹配数;
 * A 为覆盖中的左部点, B 为覆盖中的右部点, A.size()+B.size() 等于返回值.
 * 做法: 从左部所有未匹配点出发走交错路 (左到右走任意边,
 * 右到左走匹配边), 标记到达的点 visL, visR.
 * 最小点覆盖 = 左部未标记的点 + 右部已标记的点;
 * 最大独立集 = 左部已标记的点 + 右部未标记的点.
 * 跑完后 mL, mR 也是一组最大匹配.
 * Usage: init(n,m); // 每组数据先调用
 * for(int i=1;i<=k;i++){
 *   cin>>u>>v; // 左 u, 右 v
 *   g[u].push_back(v);
 * }
 * vector<int> A,B;
 * int sz=cover(A,B); // 最小点覆盖大小
 * for(int x:A) cout<<'L'<<x<<' '; // 覆盖中的左部点
 * for(int y:B) cout<<'R'<<y<<' '; // 覆盖中的右部点
 * // 最大独立集: 左部 visL[u] 为真的点, 右部 visR[v] 为假的点
 * Time: O(E \sqrt{V})
 */
#pragma once

#include "HopcroftKarp.h"

bool visL[N],visR[N];
int cover(vector<int>&A,vector<int>&B){
	int res=hk();
	for(int i=1;i<=n;i++)visL[i]=0;
	for(int i=1;i<=m;i++)visR[i]=0;
	vector<int>st;
	for(int i=1;i<=n;i++){
		if(!mL[i]){
			visL[i]=1;
			st.push_back(i);
		}
	}
	while(!st.empty()){
		int u=st.back();
		st.pop_back();
		for(int v:g[u]){
			if(visR[v])continue;
			visR[v]=1;
			int w=mR[v]; // v 一定已匹配
			if(!visL[w]){
				visL[w]=1;
				st.push_back(w);
			}
		}
	}
	A.clear();
	B.clear();
	for(int i=1;i<=n;i++){
		if(!visL[i])A.push_back(i);
	}
	for(int i=1;i<=m;i++){
		if(visR[i])B.push_back(i);
	}
	return res;
}
