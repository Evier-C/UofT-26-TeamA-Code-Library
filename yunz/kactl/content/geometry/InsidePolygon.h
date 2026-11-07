/**
 * Description: 判断点是否在简单多边形内 (顺时针或逆时针, 可以是凹的).
 * T 为 ll 时结果精确, 注意乘积溢出.
 * Usage: vector<Point> p={Point(0,0),Point(4,0),Point(0,4)};
 * bool a=inPolygon(p,Point(1,1)); // true, strict 默认 true
 * // strict 为 true 时边界上的点返回 false
 * bool b=inPolygon(p,Point(2,0),true); // false
 * bool c=inPolygon(p,Point(2,0),false); // true, 含边界
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
