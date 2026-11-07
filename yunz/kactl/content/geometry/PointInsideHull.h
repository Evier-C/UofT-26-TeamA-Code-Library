/**
 * Description: 判断点 p 是否在凸包 l (逆时针, 无共线点) 内, 在内则返回 true.
 * strict 为 true 时边界上的点不算在内. 凸包可以只有 1 或 2 个点.
 * Usage: vector<Point> h=convexHull(pts);
 * bool in=inHull(h,p,false); // 含边界
 * Time: O(\log n)
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "OnSegment.h"

bool inHull(vector<Point>&l,Point p,bool strict=true){
	int a=1,b=l.size()-1,r=!strict;
	if(l.size()<3)return r&&onSegment(l[0],l.back(),p);
	if(sideOf(l[0],l[a],l[b])>0)swap(a,b);
	if(sideOf(l[0],l[a],p)>=r||sideOf(l[0],l[b],p)<=-r)
		return false;
	while(abs(a-b)>1){ // 二分 p 所在的扇形
		int c=(a+b)/2;
		if(sideOf(l[0],l[c],p)>0)b=c;
		else a=c;
	}
	return sgn(cross(l[a],l[b],p))<r;
}
