/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: 变换到一组基, 使得形如
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$ 的卷积可快速计算,
 * 其中 $\oplus$ 为 AND, OR, XOR 之一 (默认 XOR, 其余换用注释中的行). $a$ 的长度必须是 2 的幂.
 * point\_add / point\_eval 在变换后的数组上对原数组单点加 / 单点求值.
 * Usage: vl c = conv(a, b); // a, b 等长, 长度为 2 的幂
 * FST(a, 0); point_add(a, i, v); ll x = point_eval(a, i);
 * Time: O(N \log N), 单点操作 O(N)
 * Status: stress-tested
 */
#pragma once

using vl=vector<ll>;
void FST(vl&a,bool inv){
    for(int n=sz(a),step=1;step<n;step*=2){
        for(int i=0;i<n;i+=2*step)rep(j,i,i+step){
            ll&u=a[j],&v=a[j+step];tie(u,v)=
                // inv ? pair(v - u, u) : pair(v, u + v); // AND /// include-line
                // inv ? pair(v, u - v) : pair(u + v, u); // OR /// include-line
                pair(u+v,u-v); // XOR
        }
    }
    if(inv)for(ll&x:a)x/=sz(a); // XOR
}
vl conv(vl a,vl b){
    FST(a,0);FST(b,0);
    rep(i,0,sz(a))a[i]*=b[i];
    FST(a,1);return a;
}
int psgn(int x){return __builtin_popcount(x)&1?-1:1;}
// 原数组 a[i] += val, 此处 a 已变换
void point_add(vl&a,int i,ll val){
    rep(j,0,sz(a))
        // a[j] += val * ((i|j) == sz(a)-1); // AND /// include-line
        // a[j] += val * ((i&j) == 0); // OR /// include-line
        a[j]+=val*psgn(i&j); // XOR
}
// 返回原数组 a[i], 此处 a 已变换
ll point_eval(const vl&a,int i){
    ll res=0;
    rep(j,0,sz(a))
        // res += a[j] * ((i&j) == 0) * psgn(sz(a)-1-(i|j)); // AND /// include-line
        // res += a[j] * ((i|j) == sz(a)-1) * psgn(i&j); // OR /// include-line
        res+=a[j]*psgn(i&j); // XOR
    res/=sz(a); // XOR
    return res;
}