/**
 * Description: 射线法判断点 a 是否在多边形 p 内, 在内返回 true.
 * 多边形为 vector<Point> (下标 0..n-1), 顺时针或逆时针均可, 可以是凹多边形 (要求简单多边形).
 * 点在边界上时: strict 为 true 返回 false, strict 为 false 返回 true.
 * 边界判断用 onSegment (带 eps). T 为 ll 时结果精确, 中间有乘积, 注意溢出.
 * Usage: vector<Point> p={Point(0,0),Point(4,0),Point(0,4)};
 * bool a=inPolygon(p,Point(1,1)); // true, 严格在内部
 * bool b=inPolygon(p,Point(2,0),false); // true, 含边界
 * bool c=inPolygon(p,Point(2,0),true); // false
 * Time: O(n)
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

bool inPolygon(vector<Point>&p,Point a,bool strict=true){
	int cnt=0,n=p.size();
	for(int i=0;i<n;i++){
		Point q=p[(i+1)%n];
		if(onSegment(p[i],q,a))return !strict;
		// 射线法: 向右的水平射线与边相交的次数
		cnt^=((a.y<p[i].y)-(a.y<q.y))*a.cross(p[i],q)>0;
	}
	return cnt;
}
