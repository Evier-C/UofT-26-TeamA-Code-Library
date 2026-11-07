/**
 * Description: 求圆 $(a, r1)$ 与圆 $(b, r2)$ 的两个交点, 写入 out; 无交点时返回 false.
 * 相切时两个交点相同. 两圆同心时要求 $r1 \neq r2$ (有 assert). 要求 T 为 double.
 * Usage: pair<Point,Point> out;
 * if(circleInter(a,b,r1,r2,out)) // 交点 out.first, out.second
 */
#pragma once

#include "Point.h"

bool circleInter(Point a,Point b,double r1,double r2,
		pair<Point,Point>&out){
	if(a==b){assert(r1!=r2);return false;}
	Point v=b-a;
	double d2=len2(v),sum=r1+r2,dif=r1-r2;
	double p=(d2+r1*r1-r2*r2)/(d2*2),h2=r1*r1-p*p*d2;
	if(sum*sum<d2||dif*dif>d2)return false;
	Point mid=a+v*p,per=perp(v)*sqrt(max(0.0,h2)/d2);
	out={mid+per,mid-per};
	return true;
}
