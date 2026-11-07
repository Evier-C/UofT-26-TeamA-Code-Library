/**
 * Description: 二分图最小点覆盖 (大小等于最大匹配) 与最大独立集.
 * 配合 HopcroftKarp 对象使用; 本文件全局对象为 VC.
 * Usage: HK.init(n,m); // 每组数据先调用
 * for(int i=1;i<=k;i++){
 *   cin>>u>>v; // 左 u, 右 v
 *   HK.g[u].push_back(v);
 * }
 * vector<int> A,B; // 不需要先调用 HK.hk()
 * int sz=VC.cover(HK,A,B); // 最小点覆盖大小
 * for(int x:A) cout<<'L'<<x<<' '; // 覆盖中的左部点
 * for(int y:B) cout<<'R'<<y<<' '; // 覆盖中的右部点
 * // 最大独立集: 左部 visL 为真的点 + 右部 visR 为假的点
 * for(int x=1;x<=n;x++) if(VC.visL[x]) cout<<'L'<<x<<' ';
 * for(int y=1;y<=m;y++) if(!VC.visR[y]) cout<<'R'<<y<<' ';
 * // 跑完后 HK.mL, HK.mR 为一组最大匹配
 * Time: O(E \sqrt{V})
 */
#pragma once

#include "HopcroftKarp.h"

struct VertexCover{
	static const int N=HopcroftKarp::N;
	bool visL[N],visR[N];
	int cover(HopcroftKarp&H,vector<int>&A,vector<int>&B){
		int res=H.hk();
		for(int i=1;i<=H.n;i++)visL[i]=0;
		for(int i=1;i<=H.m;i++)visR[i]=0;
		vector<int>st;
		for(int i=1;i<=H.n;i++){
			if(!H.mL[i]){
				visL[i]=1;
				st.push_back(i);
			}
		}
		while(!st.empty()){
			int u=st.back();
			st.pop_back();
			for(int v:H.g[u]){
				if(visR[v])continue;
				visR[v]=1;
				int w=H.mR[v]; // v 一定已匹配
				if(!visL[w]){
					visL[w]=1;
					st.push_back(w);
				}
			}
		}
		A.clear();
		B.clear();
		for(int i=1;i<=H.n;i++){
			if(!visL[i])A.push_back(i);
		}
		for(int i=1;i<=H.m;i++){
			if(visR[i])B.push_back(i);
		}
		return res;
	}
}VC;
