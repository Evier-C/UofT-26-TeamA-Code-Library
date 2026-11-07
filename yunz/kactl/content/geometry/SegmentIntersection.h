/**
 * Description:\\
\begin{minipage}{75mm}
两条线段 (含端点, 可退化成点) 求交.
T 为 ll 时若交点不是整点则结果错误; 中间有三个坐标的乘积, 注意溢出.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage: Point s1(0,0),e1(2,2),s2(0,2),e2(2,0);
 * vector<Point> v=segInter(s1,e1,s2,e2);
 * if(v.size()==0){} // 不相交
 * if(v.size()==1){} // 唯一交点 v[0], 这里是 (1,1)
 * // 共线重叠: 公共线段 v[0]-v[1], 按 x 再按 y 排序
 * if(v.size()==2){}
 * Time: O(1)
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

vector<Point>segInter(Point a,Point b,Point c,Point d){
	T oa=c.cross(d,a),ob=c.cross(d,b);
	T oc=a.cross(b,c),od=a.cross(b,d);
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
