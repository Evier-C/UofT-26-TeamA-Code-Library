/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: 求两圆的外公切线; 把 r2 取负则求内公切线.
 * 可能返回 0, 1 或 2 条切线 -- 0 条: 一圆包含另一圆 (求内公切线时还包括两圆相交), 或两圆相同;
 * 1 条: 两圆相切 (此时 .first = .second, 切线垂直于两圆心连线).
 * .first 和 .second 分别是圆 1 和圆 2 上的切点.
 * 求点到圆的切线时令 r2 = 0.
 * Usage:
 * 	vector<pair<P, P>> v = tangents(c1, r1, c2, r2);
 * 	// 圆 1 上切点 v[i].first, 圆 2 上切点 v[i].second
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
vector<pair<P,P>>tangents(P c1,double r1,P c2,double r2){
	P d=c2-c1;
	double dr=r1-r2,d2=d.dist2(),h2=d2-dr*dr;
	if(d2==0||h2<0)return {};
	vector<pair<P,P>>out;
	for(double sign:{-1,1}){
		P v=(d*dr+d.perp()*sqrt(h2)*sign)/d2;
		out.push_back({c1+v*r1,c2+v*r2});
	}
	if(h2==0)out.pop_back();
	return out;
}
