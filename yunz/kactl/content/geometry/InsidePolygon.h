/**
 * Description: 判断点 a 是否在多边形 p 内 (顺时针或逆时针, 可以是凹多边形).
 * strict 为 true 时边界上的点返回 false. 中间有乘积, 注意溢出.
 * Usage: vector<Point> p={Point(4,4),Point(1,2),Point(2,1)};
 * bool in=inPolygon(p,Point(3,3),false); // 含边界
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
		cnt^=((a.y<p[i].y)-(a.y<q.y))*cross(a,p[i],q)>0;
	}
	return cnt;
}
