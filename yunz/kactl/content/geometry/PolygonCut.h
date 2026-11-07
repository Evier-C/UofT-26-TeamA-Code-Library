/**
 * Description:\\
\begin{minipage}{75mm}
 用从 s 到 e 的直线切割多边形, 切掉直线左侧的部分, 返回剩余多边形的顶点 (顺序不变). 要求 T 为 double.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage: vector<Point> p; // 顶点 p[0..n-1]
 * p=polygonCut(p,Point(0,0),Point(1,0)); // 切掉 x 轴上方
 * Time: O(n)
 */
#pragma once

#include "Point.h"

vector<Point>polygonCut(vector<Point>&poly,Point s,Point e){
	vector<Point>res;
	int n=poly.size();
	for(int i=0;i<n;i++){
		Point cur=poly[i],prev=i?poly[i-1]:poly[n-1];
		double a=cross(s,e,cur),b=cross(s,e,prev);
		if((a<0)!=(b<0)) // 边与直线相交
			res.push_back(cur+(prev-cur)*(a/(a-b)));
		if(a<0)res.push_back(cur);
	}
	return res;
}
