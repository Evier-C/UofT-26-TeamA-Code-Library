/**
 * Description:\\
\begin{minipage}{75mm}
 把 p0 变到 q0, p1 变到 q1 的相似变换 (平移 + 旋转 + 缩放, 不翻转) 作用到点 r 上.
 要求 p0 与 p1 不重合, T 为 double.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{content/geometry/linearTransformation}
\vspace{-2mm}
\end{minipage}
 * Usage: Point p0(0,0),p1(1,0),q0(2,2),q1(2,4),r(1,1);
 * Point r2=linearTransformation(p0,p1,q0,q1,r); // (0,4)
 * Time: O(1)
 */
#pragma once

#include "Point.h"

Point linearTransformation(Point p0,Point p1,Point q0,
		Point q1,Point r){
	Point dp=p1-p0,dq=q1-q0;
	Point num(dp.cross(dq),dp.dot(dq));
	Point v=r-p0;
	return q0+Point(v.cross(num),v.dot(num))/dp.len2();
}
