/**
 * Author: Shashank Bhatt
 * License: CC0
 * Description: 换根 DP (0 起编号), 要求 + 满足结合律和交换律.
 * operator+ 把多个儿子合并为一个值.
 * promote() 求一个儿子对父亲的贡献.
 * Usage: vector<pii> el; // n - 1 条树边 (a, b), 第 i 条边编号 i
 * vector<ART> res = AllRoots<ART>::calc(el); // 各点为根的答案
 * Time: O(N).
 * Status: Tested on https://cses.fi/problemset/result/16593762/ and https://cses.fi/problemset/result/16593328/.
 */
#pragma once

struct ART{
  // 默认构造必须是单位元
  int ans=0; // 到其他点的最远距离
  ART operator+(const ART&o)const{
    return {max(ans,o.ans)};
  }
  ART promote(int x,int e)const{
    if(e==-1)return *this;
    return {ans+1}; // x 为点编号 ; e 为边编号
  }
};
ART base{}; // 单点的值 , 不一定是单位元
template<class T>
struct AllRoots{
  int n;vector<vector<pii>>adj;
  vector<vector<T>>suf;vector<T>res;
  AllRoots(vector<pii>&el):n(sz(el)+1),adj(n),suf(n),res(n){
    for(int ei=-1;auto[a,b]:el){ei++;
      adj[a].push_back({b,ei});
      adj[b].push_back({a,ei});
    }
    for(auto&s:suf)s.push_back(base); // 点的初始值
  }
  T down(int x,int p=-1){
    for(auto&c:adj[x])
      if(c.first==p)swap(c,adj[x][0]);
    for(int i=sz(adj[x])-1;i>-(p<0);--i)
      suf[x].push_back(down(adj[x][i].first,x)+suf[x].back());
    return (p==-1?T{}:suf[x].back().promote(x,adj[x][0].second));
  }
  void up(int x,int p=-1){
    rep(i,p!=-1,sz(adj[x])){
      auto[y,ei]=adj[x][i];
      suf[x].pop_back();
      res[y]=(res[x]+suf[x].back()).promote(x,ei);
      res[x]=res[x]+suf[y].back().promote(y,ei);
      up(y,x);
    }
  }
  static vector<T>calc(vector<pii>&el){
    AllRoots ar(el);
    ar.down(0);
    ar.up(0);
    rep(i,0,ar.n)ar.res[i]=ar.res[i].promote(i,-1);
    return ar.res;
  }
};