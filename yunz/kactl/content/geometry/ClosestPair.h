/**
 * Description: 平面最近点对 (按 y 扫描 + set 维护 x 坐标在窗口内的点).
 * Usage: vector<Point> v; // v[0..n-1], n 至少为 2
 * pair<Point,Point> pq=closest(v);
 * T d2=len2(pq.first-pq.second); // 最近距离的平方
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

pair<Point,Point>closest(vector<Point>v){
	assert(v.size()>1);
	set<Point>S; // 按 x 排序
	sort(v.begin(),v.end(),[](Point a,Point b){
		return a.y<b.y;});
	T best=LLONG_MAX;pair<Point,Point>ret;
	int j=0;
	for(Point p:v){
		Point d(1+(ll)sqrt((double)best),0); // 当前答案的上界
		while(v[j].y<=p.y-d.x)S.erase(v[j++]);
		auto lo=S.lower_bound(p-d),hi=S.upper_bound(p+d);
		for(;lo!=hi;lo++)if(len2(*lo-p)<best)
			best=len2(*lo-p),ret={*lo,p};
		S.insert(p);
	}
	return ret;
}
