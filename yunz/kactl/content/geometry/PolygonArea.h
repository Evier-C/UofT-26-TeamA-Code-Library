/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: 返回多边形有向面积的两倍.
 *  顶点按顺时针给出时面积为负. T 为 int 时注意溢出!
 * Usage:
 * 	vector<Point<ll>> v = {...}; // 多边形顶点
 * 	ll a2 = polygonArea2(v); // 有向面积的 2 倍
 * Status: Stress-tested and tested on kattis:polygonarea
 */
#pragma once

#include "Point.h"

template<class T>
T polygonArea2(vector<Point<T>>&v){
	assert(!v.empty()); // 或返回 0
	T a=v.back().cross(v[0]);
	rep(i,0,sz(v)-1)a+=v[i].cross(v[i+1]);
	return a;
}
