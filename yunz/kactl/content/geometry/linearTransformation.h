/**
 * Description:\\
\begin{minipage}{75mm}
 对点 r 施加把直线 p0-p1 变到直线 q0-q1 的线性变换 (平移, 旋转和缩放), 要求 T 为 double.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{content/geometry/linearTransformation}
\vspace{-2mm}
\end{minipage}
 * Usage: Point r2=linearTransformation(p0,p1,q0,q1,r);
 */
#pragma once

#include "Point.h"

Point linearTransformation(Point p0,Point p1,Point q0,
		Point q1,Point r){
	Point dp=p1-p0,dq=q1-q0,num(cross(dp,dq),dot(dp,dq));
	return q0+Point(cross(r-p0,num),dot(r-p0,num))/len2(dp);
}
