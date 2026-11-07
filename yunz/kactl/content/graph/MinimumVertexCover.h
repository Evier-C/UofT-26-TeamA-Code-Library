/**
 * Description: 二分图最小点覆盖 (König 定理), 大小等于最大匹配数.
 * 先跑 hk(), 再从左部所有未匹配点出发走交错路 (左到右走任意边,
 * 右到左走匹配边), 标记到达的点 visL, visR.
 * 最小点覆盖 = 左部未标记的点 + 右部已标记的点;
 * 其补集 (左部已标记 + 右部未标记) 为最大独立集.
 * Usage: init(n,m); g[u].push_back(v); // 同 HopcroftKarp
 * vector<int> A,B; int k=cover(A,B); // 覆盖左部点 A, 右部点 B
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
	for(int i=1;i<=n;i++)if(!mL[i])st.push_back(i),visL[i]=1;
	while(!st.empty()){
		int u=st.back();st.pop_back();
		for(int v:g[u])if(!visR[v]){
			visR[v]=1;int w=mR[v]; // v 一定已匹配
			if(!visL[w])visL[w]=1,st.push_back(w);
		}
	}
	A.clear();B.clear();
	for(int i=1;i<=n;i++)if(!visL[i])A.push_back(i);
	for(int i=1;i<=m;i++)if(visR[i])B.push_back(i);
	return res; // A.size()+B.size() 等于 res
}
