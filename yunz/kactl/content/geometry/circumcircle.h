/**
 * Description:\\
\begin{minipage}{75mm}
三角形的外接圆. 要求 T 为 double, 三点不共线.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * Usage: Point A(0,0),B(2,0),C(0,2);
 * double r=ccRadius(A,B,C); // 半径 sqrt(2)
 * Point o=ccCenter(A,B,C); // 圆心 (1,1)
 * Time: O(1)
 */
#pragma once

#include "Point.h"

double ccRadius(Point A,Point B,Point C){
	double a=(C-B).len(),b=(A-C).len(),c=(B-A).len();
	return a*b*c/fabs((B-A).cross(C-A))/2; // abc/(4S)
}
Point ccCenter(Point A,Point B,Point C){
	Point b=C-A,c=B-A;
	return A+(b*c.len2()-c*b.len2()).perp()/b.cross(c)/2;
}
