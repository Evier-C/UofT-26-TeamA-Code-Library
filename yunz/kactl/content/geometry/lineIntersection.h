/**
 * Description:\\
\begin{minipage}{75mm}
两条直线 (不是线段) 求交, 要求 s1 与 e1 不重合, s2 与 e2 不重合.
T 为 ll 时若交点不是整点则结果错误; 中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage: Point s1(0,0),e1(1,1),s2(0,2),e2(2,0);
 * pair<int,Point> r=lineInter(s1,e1,s2,e2);
 * if(r.first==1){} // 唯一交点 r.second, 这里是 (1,1)
 * if(r.first==0){} // 平行不重合, 无交点
 * if(r.first==-1){} // 两直线重合
 * Time: O(1)
 */
#pragma once

#include "Point.h"

pair<int,Point>lineInter(Point s1,Point e1,Point s2,Point e2){
	T d=(e1-s1).cross(e2-s2);
	if(sgn(d)==0){ // 平行, 再判断是否重合
		int same=sgn(s1.cross(e1,s2))==0;
		return {-same,Point(0,0)};
	}
	T p=s2.cross(e1,e2);
	T q=s2.cross(e2,s1);
	return {1,(s1*p+e1*q)/d};
}
