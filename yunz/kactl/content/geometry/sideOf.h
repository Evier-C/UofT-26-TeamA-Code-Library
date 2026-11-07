/**
 * Description: 返回从 $s$ 看向 $e$ 时 $p$ 所在的位置. 1/0/-1 $\Leftrightarrow$ 左侧/在直线上/右侧.
 * 带参数 $lim$ 的版本: $p$ 到直线距离不超过 $lim$ 时返回 0 (要求 $s \neq e$).
 * 中间有乘积, 注意溢出.
 * Usage: bool left=sideOf(p1,p2,q)==1; // q 在 p1 到 p2 左侧
 * int s=sideOf(p1,p2,q,1e-6); // 距离不超过 1e-6 算在线上
 */
#pragma once

#include "Point.h"

int sideOf(Point s,Point e,Point p){return sgn(cross(s,e,p));}
int sideOf(Point s,Point e,Point p,double lim){
	double a=cross(s,e,p),l=len(e-s)*lim;
	return (a>l)-(a<-l);
}
