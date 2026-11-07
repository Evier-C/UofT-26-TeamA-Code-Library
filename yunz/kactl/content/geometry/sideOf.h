/**
 * Description: 判断点在有向直线 $s \to e$ 的哪一侧. 带距离的版本要求 $s \neq e$.
 * T 为 ll 时第一个版本结果精确, 注意乘积溢出.
 * Usage: Point s(0,0),e(1,0),q(5,1);
 * int a=sideOf(s,e,q); // 1 左侧, 0 在线上, -1 右侧
 * // q 到直线距离不超过 1e-6 时算在线上, 返回 0
 * int b=sideOf(s,e,q,1e-6);
 * Time: O(1)
 */
#pragma once

#include "Point.h"

int sideOf(Point s,Point e,Point p){
	return sgn(s.cross(e,p));
}
int sideOf(Point s,Point e,Point p,double lim){
	double a=s.cross(e,p);
	double l=(e-s).len()*lim;
	return (a>l)-(a<-l);
}
