/**
 * Description: 当且仅当 p 在线段 se 上 (含端点) 时返回 true.
 * 浮点坐标的误差已由 sgn 的 eps 处理.
 * Usage: bool on=onSegment(s,e,p);
 */
#pragma once

#include "Point.h"

bool onSegment(Point s,Point e,Point p){
	return sgn(cross(p,s,e))==0&&sgn(dot(s-p,e-p))<=0;
}
