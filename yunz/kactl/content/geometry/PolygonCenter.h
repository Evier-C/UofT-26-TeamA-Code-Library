/**
 * Description: 返回多边形 (面积非 0) 的重心 (质心). 要求 T 为 double.
 * Usage: vector<Point> v; // 顶点 v[0..n-1]
 * Point c=polygonCenter(v);
 * Time: O(n)
 */
#pragma once

#include "Point.h"

Point polygonCenter(vector<Point>&v){
	Point res(0,0);double A=0;
	for(int i=0,j=v.size()-1;i<(int)v.size();j=i++){
		res=res+(v[i]+v[j])*cross(v[j],v[i]);
		A+=cross(v[j],v[i]);
	}
	return res/A/3;
}
