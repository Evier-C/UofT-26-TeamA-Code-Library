/**
 * Description: 判断点 p 是否在线段 se 上 (含两个端点), 是则返回 true.
 * 即 p, s, e 共线且 p 在 s 与 e 之间. s 与 e 重合时判断 p 是否就是这个点.
 * 浮点坐标的误差由 sgn 的 eps 处理; T 为 ll 时结果精确, 注意乘积溢出.
 * Usage: Point s(0,0),e(4,2);
 * bool a=onSegment(s,e,Point(2,1)); // true
 * bool b=onSegment(s,e,Point(6,3)); // false, 在延长线上
 * Time: O(1)
 */
#pragma once

#include "Point.h"

bool onSegment(Point s,Point e,Point p){
	return sgn(cross(p,s,e))==0&&sgn(dot(s-p,e-p))<=0;
}
