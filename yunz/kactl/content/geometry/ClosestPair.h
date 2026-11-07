/**
 * Description: 平面最近点对, 可有重复点 (此时答案为 0). T 为 ll 时结果精确, 坐标约 $10^9$ 以内.
 * Usage: vector<Point> v; // v[0..n-1], n 至少为 2
 * pair<Point,Point> pq=closest(v); // 最近的两个点
 * T d2=(pq.first-pq.second).len2(); // 最近距离的平方
 * double d=sqrt((double)d2); // 最近距离
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

bool cmpY(Point a,Point b){return a.y<b.y;}
pair<Point,Point>closest(vector<Point>v){
	assert(v.size()>1);
	set<Point>S; // 按 x 排序
	sort(v.begin(),v.end(),cmpY);
	T best=LLONG_MAX; // 当前最近距离的平方
	pair<Point,Point>ret;
	int j=0;
	for(Point p:v){
		Point d(1+(ll)sqrt((double)best),0); // 当前答案的上界
		while(v[j].y<=p.y-d.x){ // 删去 y 差太大的点
			S.erase(v[j]);
			j++;
		}
		auto lo=S.lower_bound(p-d),hi=S.upper_bound(p+d);
		for(auto it=lo;it!=hi;it++){
			if((*it-p).len2()<best){
				best=(*it-p).len2();
				ret={*it,p};
			}
		}
		S.insert(p);
	}
	return ret;
}
