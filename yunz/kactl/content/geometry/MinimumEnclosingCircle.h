/**
 * Description: 最小圆覆盖 (随机增量法). 返回 \{圆心, 半径\}, 要求 T 为 double.
 * Usage: vector<Point> ps; // ps[0..n-1], n 至少为 1
 * pair<Point,double> c=mec(ps); // 圆心 c.first, 半径 c.second
 * Time: 期望 O(n)
 */
#pragma once

#include "circumcircle.h"

pair<Point,double>mec(vector<Point>ps){
	shuffle(ps.begin(),ps.end(),mt19937(time(0)));
	int n=ps.size();
	Point o=ps[0];
	double r=0,E=1+1e-8; // 相对误差
	for(int i=0;i<n;i++)if(len(o-ps[i])>r*E){
		o=ps[i],r=0;
		for(int j=0;j<i;j++)if(len(o-ps[j])>r*E){
			o=(ps[i]+ps[j])/2;
			r=len(o-ps[i]);
			for(int k=0;k<j;k++)if(len(o-ps[k])>r*E){
				o=ccCenter(ps[i],ps[j],ps[k]);
				r=len(o-ps[i]);
			}
		}
	}
	return {o,r};
}
