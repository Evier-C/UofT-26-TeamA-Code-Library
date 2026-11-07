/**
 * Description: 多边形有向面积的两倍. T 为 ll 时结果精确, 注意溢出.
 * Usage: vector<Point> v={Point(0,0),Point(4,0),Point(0,3)};
 * T a2=polygonArea2(v); // 12, 逆时针为正, 顺时针为负
 * double S=fabs(a2)/2; // 面积 6, 空多边形为 0
 * if(a2<0)reverse(v.begin(),v.end()); // 改成逆时针
 * Time: O(n)
 */
#pragma once

#include "Point.h"

T polygonArea2(vector<Point>&v){
	int n=v.size();
	T a=0;
	for(int i=0;i<n;i++){
		a+=v[i].cross(v[(i+1)%n]);
	}
	return a;
}
