/**
 * Description:\\
\begin{minipage}{75mm}
若线段 s1-e1 与 s2-e2 有唯一交点, 返回只含该点的 vector; 无交点返回空 vector;
有无穷多交点时返回 2 个元素, 即公共线段的两个端点 (按 x 再按 y 排序).
T 为 ll 时若交点不是整点则结果错误.
中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage: vector<Point> v=segInter(s1,e1,s2,e2);
 * if(v.size()==1) // 唯一交点 v[0]
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

vector<Point>segInter(Point a,Point b,Point c,Point d){
	T oa=cross(c,d,a),ob=cross(c,d,b);
	T oc=cross(a,b,c),od=cross(a,b,d);
	// 交点唯一且不是端点
	if(sgn(oa)*sgn(ob)<0&&sgn(oc)*sgn(od)<0)
		return {(a*ob-b*oa)/(ob-oa)};
	set<Point>s;
	if(onSegment(c,d,a))s.insert(a);
	if(onSegment(c,d,b))s.insert(b);
	if(onSegment(a,b,c))s.insert(c);
	if(onSegment(a,b,d))s.insert(d);
	return vector<Point>(s.begin(),s.end());
}
