/**
 * Description:\\
\begin{minipage}{75mm}
返回点 p 到线段 se 的最短距离 (端点包含在线段内). s 与 e 可以重合, 此时为两点距离.
p 在 se 外侧时取到端点的距离, 否则取到直线的距离. T 为 double 或 ll 均可.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage: Point s(0,0),e(2,2),p(1,1),q(3,3);
 * double d1=segDist(s,e,p); // 得 0, 即 p 在线段上
 * double d2=segDist(s,e,q); // 得 sqrt(2), 到端点 e
 * Time: O(1)
 */
#pragma once

#include "Point.h"

double segDist(Point s,Point e,Point p){
	// 投影落在 s 外侧或 e 外侧时取端点距离
	if(s==e||sgn(dot(p-s,e-s))<0)return len(p-s);
	if(sgn(dot(p-e,s-e))<0)return len(p-e);
	return fabs((double)cross(s,e,p))/len(e-s);
}
