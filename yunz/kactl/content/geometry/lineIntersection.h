/**
 * Description:\\
\begin{minipage}{75mm}
若过 s1,e1 的直线与过 s2,e2 的直线有唯一交点, 返回 \{1, 交点\};
无交点 (平行) 返回 \{0, (0,0)\}; 有无穷多交点 (重合) 返回 \{-1, (0,0)\}.
T 为 ll 时若交点不是整点则结果错误.
中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage: pair<int,Point> r=lineInter(s1,e1,s2,e2);
 * if(r.first==1) // 交点为 r.second
 */
#pragma once

#include "Point.h"

pair<int,Point>lineInter(Point s1,Point e1,Point s2,Point e2){
	T d=cross(e1-s1,e2-s2);
	if(sgn(d)==0) // 平行
		return {-(sgn(cross(s1,e1,s2))==0),Point(0,0)};
	T p=cross(s2,e1,e2),q=cross(s2,e2,s1);
	return {1,(s1*p+e1*q)/d};
}
