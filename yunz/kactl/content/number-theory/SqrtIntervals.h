/**
 * Author: Kelly Dance, ChatGPT
 * Description: 将 1..n 按顺序划分为若干闭区间，使每个区间内 $\lfloor \frac{n}{i} \rfloor$（或 $\lceil \frac{n}{i} \rceil$）不变。
 * Usage: for (auto [l, r] : fdivSplit(n)) // 段内 n/i 下取整相同
 * cdivSplit(n) 同理 , 对应上取整
 * Source: https://github.com/kelly-dance/mactl/blob/main/content/various/SqrtIntervals.h
 * Time: $O(\sqrt N)$
 * Status: stress-tested
 */
#pragma once

auto fdivSplit=[](int n){
    vector<pii>segs;
    for(int q,r,l=1;l<=n;l=r+1){
        q=n/l,r=n/q;
        segs.push_back({l,r});
    }
    return segs;
};
auto cdivSplit=[](int n){
    auto segs=fdivSplit(n-1);
    segs.push_back({n,n});
    return segs;
};