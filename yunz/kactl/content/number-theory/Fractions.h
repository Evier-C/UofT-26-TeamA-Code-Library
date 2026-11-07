/**
 * Author: Robert Chung
 * Source: None
 * Description: 分数类（自动约分）。乘积可能溢出，需注意。
 * Usage: frac a(1, 2), b(1, 3); frac c = a + b; // 5/6
 * Status: tested on https://open.kattis.com/submissions/19398895
 */
#pragma once

struct frac{
    int p,q;
    frac(int p=0,int q=1):p(p),q(q){norm();}
    void norm(){assert(q);
        if(q<0)p=-p,q=-q;
        int g=gcd(p,q);
        p/=g,q/=g;}
    frac&operator+=(frac o){
        tie(p,q)=pair(p*o.q+q*o.p,q*o.q);
        norm();return *this;}
    frac&operator-=(frac o){
        tie(p,q)=pair(p*o.q-q*o.p,q*o.q);
        norm();return *this;}
    frac&operator*=(frac o){
        tie(p,q)=pair(p*o.p,q*o.q);
        norm();return *this;}
    frac&operator/=(frac o){
        tie(p,q)=pair(p*o.q,q*o.p);
        norm();return *this;}
    friend frac operator+(frac a,frac b){return a+=b;}
    friend frac operator-(frac a,frac b){return a-=b;}
    friend frac operator*(frac a,frac b){return a*=b;}
    friend frac operator/(frac a,frac b){return a/=b;}
    friend bool operator==(frac a,frac b)=default;
    friend bool operator<(frac a,frac b){return a.p*b.q<a.q*b.p;}
    friend ostream&operator<<(ostream&os,frac a){
        return os<<a.p<<'/'<<a.q;}
};