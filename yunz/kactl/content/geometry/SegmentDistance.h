/**
 * Description:\\
\begin{minipage}{75mm}
返回点 p 到线段 se 的最短距离.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage: Point s(0,0),e(2,2),p(1,1);
 * double d=segDist(s,e,p); // 得 0, 即 p 在线段上
 */
#pragma once

#include "Point.h"

double segDist(Point s,Point e,Point p){
	// 投影落在 s 外侧或 e 外侧时取端点距离
	if(s==e||sgn(dot(p-s,e-s))<0)return len(p-s);
	if(sgn(dot(p-e,s-e))<0)return len(p-e);
	return fabs((double)cross(s,e,p))/len(e-s);
}
