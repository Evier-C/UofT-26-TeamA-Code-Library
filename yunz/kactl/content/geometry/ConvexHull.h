/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\\begin{minipage}{75mm}
按逆时针顺序返回凸包上的点.
位于凸包边上 (在另外两点之间) 的点不算在凸包内.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Usage:
 * 	vector<P> hull = convexHull(pts);
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

typedef Point<ll>P;
vector<P>convexHull(vector<P>pts){
	if(sz(pts)<=1)return pts;
	sort(all(pts));
	vector<P>h(sz(pts)+1);
	int s=0,t=0;
	for(int it=2;it--;s=--t,reverse(all(pts)))
		for(P p:pts){
			while(t>=s+2&&h[t-2].cross(h[t-1],p)<=0)t--;
			h[t++]=p;
		}
	return {h.begin(),h.begin()+t-(t==2&&h[0]==h[1])};
}
