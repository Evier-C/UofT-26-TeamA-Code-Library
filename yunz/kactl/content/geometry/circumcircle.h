/**
 * Description:\\
\begin{minipage}{75mm}
三角形的外接圆 (经过三个顶点的圆). ccRadius 返回过 A, B, C 三点的圆的半径,
ccCenter 返回该圆的圆心. 要求 T 为 double, 三点不共线 (否则除以 0).
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * Usage: Point A(0,0),B(2,0),C(0,2);
 * double r=ccRadius(A,B,C); // sqrt(2)
 * Point o=ccCenter(A,B,C); // (1,1)
 * Time: O(1)
 */
#pragma once

#include "Point.h"

double ccRadius(Point A,Point B,Point C){
	return len(B-A)*len(C-B)*len(A-C)/fabs(cross(B-A,C-A))/2;
}
Point ccCenter(Point A,Point B,Point C){
	Point b=C-A,c=B-A;
	return A+perp(b*len2(c)-c*len2(b))/cross(b,c)/2;
}
