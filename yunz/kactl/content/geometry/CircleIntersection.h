/**
 * Description: 两圆的圆周交点, 要求 T 为 double.
 * 两圆心重合时返回 false, 且要求 $r1 \neq r2$ (有 assert).
 * Usage: Point a(0,0),b(2,0);
 * pair<Point,Point> out;
 * if(circleInter(a,b,2,2,out)){ // 圆 (a,2) 与圆 (b,2)
 *   // out.first=(1,sqrt(3)), out.second=(1,-sqrt(3))
 *   // 从 a 看向 b, first 在左侧; 相切时两点相同
 * }else{} // 相离, 内含或同心
 * Time: O(1)
 */
#pragma once

#include "Point.h"

bool circleInter(Point a,Point b,double r1,double r2,
		pair<Point,Point>&out){
	if(a==b){
		assert(r1!=r2);
		return false;
	}
	Point v=b-a;
	double d2=v.len2(),sum=r1+r2,dif=r1-r2;
	if(sum*sum<d2||dif*dif>d2)return false;
	// p: 交点连线中点在 ab 上的比例, h2: 半弦长平方的比例
	double p=(d2+r1*r1-r2*r2)/(d2*2);
	double h2=r1*r1-p*p*d2;
	Point mid=a+v*p;
	Point per=v.perp()*sqrt(max(0.0,h2)/d2);
	out={mid+per,mid-per};
	return true;
}
