/**
 * Description:\\
\begin{minipage}{75mm}
点到直线的有向距离, 要求 a 与 b 不重合. T 为 ll 时也可用.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Usage: Point a(0,0),b(2,0),p(1,3);
 * double d=lineDist(a,b,p); // 3, p 在 a 看向 b 左侧为正
 * double h=fabs(d); // 点到直线距离
 * Time: O(1)
 */
#pragma once

#include "Point.h"

double lineDist(Point a,Point b,Point p){
	return a.cross(b,p)/(b-a).len();
}
