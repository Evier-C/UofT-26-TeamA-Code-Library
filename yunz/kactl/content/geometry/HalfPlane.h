/**
 * Description: 半平面交 (极角排序 + 双端队列). 每条有向直线 $s \to e$ 表示它左侧的半平面.
 * 返回交集凸多边形的顶点 (逆时针); 交集为空或面积为 0 时返回空 (面积很小时也可能返回退化的多边形).
 * 要求交集有界: 不确定时先加入一个大矩形的 4 条边. 要求 T 为 double.
 * Usage: vector<Line> L; // L[0..n-1]
 * L.push_back({Point(0,0),Point(1,0)}); // 保留 x 轴上方
 * vector<Point> poly=halfPlane(L);
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

struct Line{Point s,e;}; // 有向直线 s 到 e
double ang(Line l){return angle(l.e-l.s);}
bool cmpLine(Line a,Line b){ // 按极角排序, 相同时靠左的在前
	if(sgn(ang(a)-ang(b)))return ang(a)<ang(b);
	return sgn(cross(a.s,a.e,b.s))<0;
}
bool onRight(Line l,Point p){return sgn(cross(l.s,l.e,p))<=0;}
Point inter(Line a,Line b){ // 两直线交点, 要求不平行
	Point u=a.e-a.s,v=b.e-b.s;
	return a.s+u*(cross(v,b.s-a.s)/cross(v,u));
}
vector<Point>halfPlane(vector<Line>L){
	sort(L.begin(),L.end(),cmpLine);
	int n=L.size(),h=0,t=-1;
	vector<Line>q(n);vector<Point>p(n); // 队列 q[h..t]
	for(int i=0;i<n;i++){
		// 同向的只留第一条, 即最靠左的
		if(i&&!sgn(ang(L[i])-ang(L[i-1])))continue;
		while(h<t&&onRight(L[i],p[t-1]))t--;
		while(h<t&&onRight(L[i],p[h]))h++;
		if(h<=t&&!sgn(cross(L[i].e-L[i].s,q[t].e-q[t].s)))
			return {}; // 与队尾反向平行, 交集为空
		q[++t]=L[i];
		if(h<t)p[t-1]=inter(q[t-1],q[t]);
	}
	while(h<t&&onRight(q[h],p[t-1]))t--;
	if(t-h<2)return {};
	p[t]=inter(q[t],q[h]);
	return vector<Point>(p.begin()+h,p.begin()+t+1);
}
