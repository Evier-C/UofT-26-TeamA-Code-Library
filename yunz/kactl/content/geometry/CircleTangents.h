/**
 * Description: 求两圆的外公切线; 把 r2 取负则求内公切线. 要求 T 为 double.
 * 可能返回 0, 1 或 2 条切线 -- 0 条: 一圆包含另一圆 (求内公切线时还包括两圆相交), 或两圆相同;
 * 1 条: 两圆相切 (此时 .first = .second, 切线垂直于两圆心连线).
 * .first 和 .second 分别是圆 1 和圆 2 上的切点.
 * 求点到圆的切线时令 r2 = 0.
 * Usage: vector<pair<Point,Point>> v=tangents(c1,r1,c2,r2);
 * // 圆 1 上切点 v[i].first, 圆 2 上切点 v[i].second
 */
#pragma once

#include "Point.h"

vector<pair<Point,Point>>tangents(Point c1,double r1,
		Point c2,double r2){
	Point d=c2-c1;
	double dr=r1-r2,d2=len2(d),h2=d2-dr*dr;
	if(sgn(d2)==0||sgn(h2)<0)return {};
	if(sgn(h2)==0)h2=0; // 相切, 只有一条
	vector<pair<Point,Point>>out;
	for(int s=-1;s<=1;s+=2){
		Point v=(d*dr+perp(d)*(sqrt(h2)*s))/d2;
		out.push_back({c1+v*r1,c2+v*r2});
	}
	if(h2==0)out.pop_back();
	return out;
}
