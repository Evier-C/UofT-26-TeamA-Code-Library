/**
 * Description: 两圆的公切线, 要求 T 为 double. 切线条数: 一圆在另一圆内 (求内公切线时还包括两圆相交)
 * 或两圆心重合时 0 条; 两圆相切时 1 条 (两个切点是同一点); 否则 2 条.
 * Usage: Point c1(0,0),c2(5,0); // 半径 1 和 2
 * vector<pair<Point,Point>> v=tangents(c1,1,c2,2); // 外
 * vector<pair<Point,Point>> w=tangents(c1,1,c2,-2); // 内
 * // v[i].first 在圆 1 上, v[i].second 在圆 2 上
 * // 点 c2 到圆 1 的切线: 令 r2=0, 切点为 first
 * vector<pair<Point,Point>> u=tangents(c1,1,c2,0);
 * Time: O(1)
 */
#pragma once

#include "Point.h"

vector<pair<Point,Point>>tangents(Point c1,double r1,
		Point c2,double r2){
	Point d=c2-c1;
	double dr=r1-r2,d2=d.len2(),h2=d2-dr*dr;
	if(sgn(d2)==0||sgn(h2)<0)return {};
	if(sgn(h2)==0)h2=0; // 相切, 只有一条
	vector<pair<Point,Point>>out;
	for(int s=-1;s<=1;s+=2){
		Point v=(d*dr+d.perp()*(sqrt(h2)*s))/d2;
		out.push_back({c1+v*r1,c2+v*r2});
	}
	if(h2==0)out.pop_back();
	return out;
}
