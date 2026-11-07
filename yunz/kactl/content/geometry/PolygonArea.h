/**
 * Description: 返回多边形有向面积的两倍.
 * 顶点按逆时针给出时为正, 顺时针为负. T 为 ll 时结果精确.
 * Usage: vector<Point> v; // 顶点 v[0..n-1]
 * T a2=polygonArea2(v); // 面积为 fabs(a2)/2
 * Time: O(n)
 */
#pragma once

#include "Point.h"

T polygonArea2(vector<Point>&v){
	int n=v.size();T a=0;
	for(int i=0;i<n;i++)a+=cross(v[i],v[(i+1)%n]);
	return a;
}
