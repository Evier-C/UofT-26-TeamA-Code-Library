/**
 * Author: Yunzhe Qiao
 * Date: 2026-03-03
 * License: None
 * Description: 离线动态图连通性 (线段树分治 + 可撤销并查集).
 * 每条边在时间区间 $[l, r]$ 内存在, 在 add\_query 的时刻求答案;
 * 默认答案为连通块个数 (点编号 $1..n$, 并查集大小 $n+1$).
 * 易错点: 若 $u > v$ 先交换 $u, v$ (方便匹配同一条边); 边在时刻 $t$
 * 被删除则结束时间为 $t-1$; 别忘了处理从未删除的边.
 * Usage: DynConn dc(T); dc.add_edge(l, r, {u, v});
 * dc.add_query(t); RollbackUF uf(n + 1);
 * dc.solve(uf); // 答案在 dc.ans[t]
 * Status: tested on https://codeforces.com/gym/100551/problem/A, cses.fi/problemset/task/2133/
 */
#pragma once

#include "UnionFindRollback.h"

struct DynConn{
    int T; // DynConn(T) 的时间范围为 [0..T]
    vector<vector<pii>>tree;
    vector<int>queries; // 按需修改询问类型
    vi ans; // 默认是连通块数 ; -1 表示此时无询问
    DynConn(int t):T(t+2),tree(4*T),queries(4*T,-1),
        ans(T,-1){}
    // [ql, qr] 为边的开始和结束时刻
    void add_edge(int ql,int qr,pii edge){
        if(ql>qr)return;
        auto f=[&](auto f,int node,int l,int r)->void{
            if(ql>r||qr<l)return;
            if(ql<=l&&r<=qr){
                tree[node].push_back(edge);
                return;
            }
            int mid=(l+r)/2;
            f(f,2*node,l,mid);
            f(f,2*node+1,mid+1,r);
        };
        f(f,1,0,T);
    }
    void add_query(int time){ // 按需加参数
        queries[time]=0;
    }
    void solve(auto&dsu){
        auto f=[&](auto f,int node,int l,int r)->void{
            int t=dsu.time();
            for(auto[a,b]:tree[node])dsu.join(a,b);
            if(l==r){
                if(queries[l]!=-1){ // 按需修改
                    ans[l]=sz(dsu.e)-1-dsu.time()/2;
                }
            }else{
                int mid=(l+r)/2;
                f(f,2*node,l,mid);
                f(f,2*node+1,mid+1,r);
            }
            dsu.rollback(t);
        };
        f(f,1,0,T);
    }
};