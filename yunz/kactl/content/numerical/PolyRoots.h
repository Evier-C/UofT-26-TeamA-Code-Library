/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: 求多项式在区间 $[xmin, xmax]$ 内的全部实根 (递归求导函数的根, 在单调段上二分).
 * Usage: polyRoots({{2,-3,1}},-1e9,1e9) // 解 x^2-3x+2 = 0
 * Time: O(n^2 \log(1/\epsilon))
 */
#pragma once

#include "Polynomial.h"

vector<double>polyRoots(Poly p,double xmin,double xmax){
	if(sz(p.a)==2){return {-p.a[0]/p.a[1]};}
	vector<double>ret;
	Poly der=p;
	der.diff();
	auto dr=polyRoots(der,xmin,xmax);
	dr.push_back(xmin-1);
	dr.push_back(xmax+1);
	sort(all(dr));
	rep(i,0,sz(dr)-1){
		double l=dr[i],h=dr[i+1];
		bool sign=p(l)>0;
		if(sign^(p(h)>0)){
			rep(it,0,60){ // while (h - l > 1e-8)
				double m=(l+h)/2,f=p(m);
				if((f<=0)^sign)l=m;
				else h=m;
			}
			ret.push_back((l+h)/2);
		}
	}
	return ret;
}
