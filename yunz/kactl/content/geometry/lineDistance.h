/**
 * Description:\\
\begin{minipage}{75mm}
返回点 p 到直线 ab 的有向距离: 从 a 看向 b, p 在左侧为正, 右侧为负, 在直线上为 0.
取绝对值即点到直线的距离. 要求 a 与 b 不重合 (否则得 nan).
T 为 ll 时也可用 (返回 double).
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Usage: Point a(0,0),b(2,0),p(1,3);
 * double d=lineDist(a,b,p); // 得 3, 正数表示 p 在左侧
 * double h=fabs(lineDist(a,b,p)); // 点到直线距离
 * Time: O(1)
 */
#pragma once

#include "Point.h"

double lineDist(Point a,Point b,Point p){
	return cross(a,b,p)/len(b-a);
}
