/**
 * Description: 返回多边形 (实心均匀薄板) 的重心 (质心), 不是顶点的平均值.
 * 多边形为 vector<Point> (下标 0..n-1), 顺时针或逆时针均可, 可以是凹多边形; 面积不能为 0.
 * 要求 T 为 double.
 * Usage: vector<Point> v={Point(0,0),Point(2,0),Point(2,2),Point(0,2)};
 * Point c=polygonCenter(v); // (1,1)
 * Time: O(n)
 */
#pragma once

#include "Point.h"

Point polygonCenter(vector<Point>&v){
	int n=v.size();
	Point res(0,0);
	double A=0; // 面积的两倍
	for(int i=0;i<n;i++){
		Point p=v[i],q=v[(i+1)%n];
		res=res+(p+q)*p.cross(q);
		A+=p.cross(q);
	}
	return res/A/3;
}
