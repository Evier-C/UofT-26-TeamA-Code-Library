/**
 * Author: Benjamin Qi, chilli
 * Date: 2020-04-04
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: 带权二分图匹配 (匈牙利算法): 给左部每个点匹配一个不同的
 * 右部点, 使边权和最小. 输入 cost[N][M], cost[i][j] 为 L[i] 匹配 R[j]
 * 的代价; 返回 (最小代价, match), L[i] 与 R[match[i]] 匹配.
 * 求最大权时把代价取负. 要求 $N \le M$.
 * Usage: vector<vector<ll>> cost(N, vector<ll>(M));
 * auto [c, mt] = hungarian(cost); // L[i] 匹配 R[mt[i]]
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, stress-tested
 */
#pragma once

template<class T>
pair<T,vector<T>>hungarian(const vector<vector<T>>&a){
  if(a.empty())return {0,{}};
  int n=sz(a)+1,m=sz(a[0])+1;
  vector<T>u(n),v(m),ans(n-1);
  vi p(m);
  rep(i,1,n){
    p[0]=i;
    int j0=0; // 加入虚拟点 0
    vector<T>dist(m,1e18); // 按需修改上界
    vi pre(m,-1);
    vector<bool>done(m+1);
    do{ // dijkstra
      done[j0]=true;
      int i0=p[j0],j1;
      T delta=1e18; // 按需修改上界
      rep(j,1,m)if(!done[j]){
          T cur=a[i0-1][j-1]-u[i0]-v[j];
          if(cur<dist[j])dist[j]=cur,pre[j]=j0;
          if(dist[j]<delta)delta=dist[j],j1=j;
        }
      rep(j,0,m){
        if(done[j])u[p[j]]+=delta,v[j]-=delta;
        else dist[j]-=delta;
      }
      j0=j1;
    }while(p[j0]);
    while(j0){ // 更新交错路
      int j1=pre[j0];
      p[j0]=p[j1],j0=j1;
    }
  }
  rep(j,1,m)if(p[j])ans[p[j]-1]=j-1;
  return {-v[0],ans}; // { 最小代价 , 匹配数组 }
}
