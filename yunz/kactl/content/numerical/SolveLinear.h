/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: 求解 $A * x = b$. 若有多解, 返回任意一个.
 *  返回秩, 无解返回 -1. $A$ 与 $b$ 的数据会被破坏.
 * Usage: vector<vd> A(n, vd(m)); vd b(n), x(m); // x 须预设长度 m
 * int r = solveLinear(A, b, x); // 无解返回 -1
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once

typedef vector<double>vd;
const double eps=1e-12;

int solveLinear(vector<vd>&A,vd&b,vd&x){
	int n=sz(A),m=sz(x),rank=0,br,bc;
	if(n)assert(sz(A[0])==m);
	vi col(m);iota(all(col),0);

	rep(i,0,n){
		double v,bv=0;
		rep(r,i,n)rep(c,i,m)
			if((v=fabs(A[r][c]))>bv)
				br=r,bc=c,bv=v;
		if(bv<=eps){
			rep(j,i,n)if(fabs(b[j])>eps)return -1;
			break;
		}
		swap(A[i],A[br]);
		swap(b[i],b[br]);
		swap(col[i],col[bc]);
		rep(j,0,n)swap(A[j][i],A[j][bc]);
		bv=1/A[i][i];
		rep(j,i+1,n){
			double fac=A[j][i]*bv;
			b[j]-=fac*b[i];
			rep(k,i+1,m)A[j][k]-=fac*A[i][k];
		}
		rank++;
	}

	x.assign(m,0);
	for(int i=rank;i--;){
		b[i]/=A[i][i];
		x[col[i]]=b[i];
		rep(j,0,i)b[j]-=A[j][i]*b[i];
	}
	return rank; // rank < m 时有多解
}
