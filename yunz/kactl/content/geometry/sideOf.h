/**
 * Description: 判断点 $p$ 在有向直线 $s \to e$ 的哪一侧:
 * 返回 1 表示左侧 (逆时针方向), 0 表示在直线上, -1 表示右侧.
 * 带参数 $lim$ 的版本按距离判断: $p$ 到直线的距离不超过 $lim$ 时返回 0, 要求 $s \neq e$.
 * T 为 ll 时第一个版本结果精确, 注意乘积溢出.
 * Usage: Point p1(0,0),p2(1,0),q(5,1);
 * int s=sideOf(p1,p2,q); // 1, q 在 p1 看向 p2 的左侧
 * int t=sideOf(p1,p2,q,1e-6); // 距离不超过 1e-6 算在线上
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
