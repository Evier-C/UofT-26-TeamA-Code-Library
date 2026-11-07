/**
 * Description: 判断点是否在线段上 (含端点). T 为 ll 时结果精确, 注意乘积溢出.
 * Usage: Point s(0,0),e(4,2);
 * bool a=onSegment(s,e,Point(2,1)); // true
 * bool b=onSegment(s,e,Point(6,3)); // false, 在延长线上
 * bool c=onSegment(s,s,s); // true, 线段可退化成点
 * Time: O(1)
 */
#pragma once

#include "Point.h"

bool onSegment(Point s,Point e,Point p){
	return sgn(p.cross(s,e))==0&&sgn((s-p).dot(e-p))<=0;
}
