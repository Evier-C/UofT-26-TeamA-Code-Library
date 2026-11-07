/**
 * Description:\\
\begin{minipage}{75mm}
求过 s1,e1 的直线与过 s2,e2 的直线的交点 (直线, 不是线段). 返回 \{状态, 交点\}:
状态 1 表示有唯一交点; 0 表示平行不重合, 无交点; -1 表示两直线重合.
后两种情况交点返回 (0,0). 要求 s1, e1 不重合, s2, e2 不重合.
T 为 ll 时若交点不是整点则结果错误; 中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage: Point s1(0,0),e1(1,1),s2(0,2),e2(2,0);
 * pair<int,Point> r=lineInter(s1,e1,s2,e2);
 * if(r.first==1){} // 交点为 r.second, 这里是 (1,1)
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
