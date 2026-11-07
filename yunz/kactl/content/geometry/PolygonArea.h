/**
 * Description: 返回多边形有向面积的两倍 (鞋带公式).
 * 多边形为 vector<Point> (下标 0..n-1), 顶点逆时针给出时为正, 顺时针为负; 面积为 fabs 后除以 2.
 * 也可用来判断多边形方向. 空多边形返回 0. T 为 ll 时结果精确 (面积两倍是整数), 注意溢出.
 * Usage: vector<Point> v={Point(0,0),Point(4,0),Point(0,3)};
 * T a2=polygonArea2(v); // 12, 逆时针为正
 * double S=fabs(a2)/2; // 面积 6
 * if(a2<0)reverse(v.begin(),v.end()); // 改成逆时针
 * Time: O(n)
 */
#pragma once

#include "Point.h"

T polygonArea2(vector<Point>&v){
	int n=v.size();
	T a=0;
	for(int i=0;i<n;i++){
		a+=cross(v[i],v[(i+1)%n]);
	}
	return a;
}
