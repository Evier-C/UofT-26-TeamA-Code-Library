/**
 * Description:\\
\begin{minipage}{75mm}
 用有向直线切割多边形, 保留直线右侧 (含直线上的点). 要求 T 为 double.
 凹多边形可能被切成几块, 结果用直线上的边连成一个多边形 (面积仍正确).
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage: vector<Point> p; // 正方形 [0,1]x[-1,1], 逆时针
 * p.push_back(Point(0,-1));
 * p.push_back(Point(1,-1));
 * p.push_back(Point(1,1));
 * p.push_back(Point(0,1));
 * // 切掉 s 看向 e 的左侧, 即 x 轴上方
 * vector<Point> q=polygonCut(p,Point(0,0),Point(1,0));
 * // q 为剩下的部分, 顶点顺序同 p, 全部切掉时为空
 * Time: O(n)
 */
#pragma once

#include "Point.h"

vector<Point>polygonCut(vector<Point>&poly,Point s,Point e){
	vector<Point>res;
	int n=poly.size();
	for(int i=0;i<n;i++){
		Point cur=poly[i];
		Point prev=i?poly[i-1]:poly[n-1];
		double a=s.cross(e,cur),b=s.cross(e,prev);
		if((a<0)!=(b<0)){ // 边与直线相交, 加入交点
			res.push_back(cur+(prev-cur)*(a/(a-b)));
		}
		if(a<0)res.push_back(cur);
	}
	return res;
}
