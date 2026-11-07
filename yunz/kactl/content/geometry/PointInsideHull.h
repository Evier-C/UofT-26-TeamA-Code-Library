/**
 * Description: 二分判断点 p 是否在凸包 l 内, 在内返回 true.
 * l 为逆时针凸包 (无重复点和共线点, 即 convexHull 的结果, 下标 0..n-1), 可以只有 1 或 2 个点.
 * 点在边界上时: strict 为 true 返回 false, strict 为 false 返回 true.
 * T 为 ll 时结果精确, 注意乘积溢出. 多次询问时每次 $O(\log n)$.
 * Usage: vector<Point> h=convexHull(pts);
 * bool a=inHull(h,p); // 严格在内部
 * bool b=inHull(h,p,false); // 含边界
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
	if(sideOf(l[0],l[a],p)>=r||sideOf(l[0],l[b],p)<=-r){
		return false;
	}
	while(abs(a-b)>1){ // 二分 p 所在的扇形
		int c=(a+b)/2;
		if(sideOf(l[0],l[c],p)>0)b=c;
		else a=c;
	}
	return sgn(l[a].cross(l[b],p))<r;
}
