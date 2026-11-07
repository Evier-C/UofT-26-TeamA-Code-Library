/**
 * Description: 半平面交 (极角排序 + 双端队列). 每条有向直线 Line\{s, e\} 表示它左侧的半平面 (含边界).
 * 返回所有半平面的交 (凸多边形) 的顶点, 逆时针, 下标 0..m-1; 交集为空或面积为 0 时返回空
 * (面积极小时也可能返回退化的多边形, 按面积判断即可).
 * 要求交集有界: 不确定时先加入一个大矩形的 4 条边 (见用法). 方向相同的直线只保留最靠里的一条.
 * 要求 T 为 double, 判断用 eps.
 * Usage: vector<Line> L; // 每条直线保留左侧
 * L.push_back({Point(0,0),Point(1,0)}); // y 不小于 0
 * double B=1e7; // 逆时针的大矩形, 保证交集有界
 * Point c[4]={Point(-B,-B),Point(B,-B),Point(B,B),Point(-B,B)};
 * for(int i=0;i<4;i++)L.push_back({c[i],c[(i+1)\%4]});
 * vector<Point> poly=halfPlane(L); // 空表示无交
 * double S=fabs(polygonArea2(poly))/2; // 交的面积
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

struct Line{
	Point s,e; // 有向直线 s 到 e, 保留左侧
};
double ang(Line l){return angle(l.e-l.s);}
bool cmpLine(Line a,Line b){ // 按极角排序, 相同时靠左的在前
	if(sgn(ang(a)-ang(b))!=0)return ang(a)<ang(b);
	return sgn(cross(a.s,a.e,b.s))<0;
}
// p 不在 l 的严格左侧
bool onRight(Line l,Point p){return sgn(cross(l.s,l.e,p))<=0;}
Point inter(Line a,Line b){ // 两直线交点, 要求不平行
	Point u=a.e-a.s,v=b.e-b.s;
	return a.s+u*(cross(v,b.s-a.s)/cross(v,u));
}
vector<Point>halfPlane(vector<Line>L){
	sort(L.begin(),L.end(),cmpLine);
	int n=L.size(),h=0,t=-1;
	vector<Line>q(n); // 队列 q[h..t]
	vector<Point>p(n); // p[i] 为 q[i] 与 q[i+1] 的交点
	for(int i=0;i<n;i++){
		// 同向的只留第一条, 即最靠左的
		if(i>0&&sgn(ang(L[i])-ang(L[i-1]))==0)continue;
		while(h<t&&onRight(L[i],p[t-1]))t--;
		while(h<t&&onRight(L[i],p[h]))h++;
		// 与队尾反向平行, 交集为空
		if(h<=t&&sgn(cross(L[i].e-L[i].s,q[t].e-q[t].s))==0){
			return {};
		}
		t++;
		q[t]=L[i];
		if(h<t)p[t-1]=inter(q[t-1],q[t]);
	}
	while(h<t&&onRight(q[h],p[t-1]))t--;
	if(t-h<2)return {};
	p[t]=inter(q[t],q[h]);
	return vector<Point>(p.begin()+h,p.begin()+t+1);
}
