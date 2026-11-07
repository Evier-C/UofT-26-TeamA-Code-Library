/**
 * Description:\\
\begin{minipage}{75mm}
返回点 p 到直线 ab 的有向距离. 从 a 看向 b, 左侧为正, 右侧为负; a 与 b 重合时得 nan.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Usage: double d=lineDist(a,b,p); // 正数表示 p 在左侧
 * double h=fabs(lineDist(a,b,p)); // 点到直线距离
 */
#pragma once

#include "Point.h"

double lineDist(Point a,Point b,Point p){
	return cross(a,b,p)/len(b-a);
}
