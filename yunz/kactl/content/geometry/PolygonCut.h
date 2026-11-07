/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 用从 s 到 e 的直线切割多边形, 切掉直线左侧的部分, 返回剩余多边形的顶点.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage:
 * 	vector<P> p = ...;
 * 	p = polygonCut(p, P(0,0), P(1,0)); // 切掉 x 轴上方
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"

typedef Point<double>P;
vector<P>polygonCut(const vector<P>&poly,P s,P e){
	vector<P>res;
	rep(i,0,sz(poly)){
		P cur=poly[i],prev=i?poly[i-1]:poly.back();
		auto a=s.cross(e,cur),b=s.cross(e,prev);
		if((a<0)!=(b<0))
			res.push_back(cur+(prev-cur)*(a/(a-b)));
		if(a<0)
			res.push_back(cur);
	}
	return res;
}
