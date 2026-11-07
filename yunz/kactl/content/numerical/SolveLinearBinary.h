/**
 * Author: Simon Lindholm
 * Date: 2016-08-27
 * License: CC0
 * Source: own work
 * Description: 在 $\mathbb F_2$ 上求解 $Ax = b$, $m$ 为未知数个数. 若有多解, 任意返回一个.
 *  返回秩, 无解返回 -1. 会破坏 $A$ 与 $b$.
 * Usage: vector<bs> A(n); vi b(n); bs x;
 * int r = solveLinear(A, b, x, m); // m 为未知数个数
 * Time: O(n^2 m)
 * Status: bruteforce-tested for n, m <= 4
 */
#pragma once

typedef bitset<1000>bs;

int solveLinear(vector<bs>&A,vi&b,bs&x,int m){
	int n=sz(A),rank=0,br;
	assert(m<=sz(x));
	vi col(m);iota(all(col),0);
	rep(i,0,n){
		for(br=i;br<n;++br)if(A[br].any())break;
		if(br==n){
			rep(j,i,n)if(b[j])return -1;
			break;
		}
		int bc=(int)A[br]._Find_next(i-1);
		swap(A[i],A[br]);
		swap(b[i],b[br]);
		swap(col[i],col[bc]);
		rep(j,0,n)if(A[j][i]!=A[j][bc]){
			A[j].flip(i);A[j].flip(bc);
		}
		rep(j,i+1,n)if(A[j][i]){
			b[j]^=b[i];
			A[j]^=A[i];
		}
		rank++;
	}

	x=bs();
	for(int i=rank;i--;){
		if(!b[i])continue;
		x[col[i]]=1;
		rep(j,0,i)b[j]^=A[j][i];
	}
	return rank; // rank < m 时有多解
}
