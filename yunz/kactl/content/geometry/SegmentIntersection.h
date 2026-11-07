/**
 * Description:\\
\begin{minipage}{75mm}
求线段 s1-e1 与线段 s2-e2 的交点 (端点算在线段上). 返回 vector:
大小为 0 表示不相交; 大小为 1 表示唯一交点 (包括端点相碰);
大小为 2 表示两线段共线且重叠, 返回公共线段的两个端点 (按 x 再按 y 排序).
线段可退化成一个点. T 为 ll 时若交点不是整点则结果错误;
中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage: Point s1(0,0),e1(2,2),s2(0,2),e2(2,0);
 * vector<Point> v=segInter(s1,e1,s2,e2);
 * if(v.size()==1){} // 唯一交点 v[0], 这里是 (1,1)
 * if(v.size()==2){} // 重叠部分为线段 v[0]-v[1]
 * Time: O(1)
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
