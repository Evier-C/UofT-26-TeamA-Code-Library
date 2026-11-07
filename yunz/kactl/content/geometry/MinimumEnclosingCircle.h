/**
 * Description: 最小圆覆盖 (所有点在圆内或圆上). 要求 T 为 double, 至少 1 个点,
 * 可有重复点和共线点. 判断点在圆外时用相对误差 1e-8.
 * Usage: vector<Point> ps={Point(0,0),Point(2,0),Point(1,1)};
 * pair<Point,double> c=mec(ps); // 传值, ps 不变
 * Point o=c.first; // 圆心 (1,0)
 * double r=c.second; // 半径 1
 * Time: 期望 O(n)
 */
#pragma once

#include "circumcircle.h"

pair<Point,double>mec(vector<Point>ps){
	shuffle(ps.begin(),ps.end(),mt19937(time(0)));
	int n=ps.size();
	Point o=ps[0];
	double r=0;
	double E=1+1e-8; // 相对误差
	for(int i=0;i<n;i++){
		if((o-ps[i]).len()<=r*E)continue;
		o=ps[i];
		r=0;
		for(int j=0;j<i;j++){
			if((o-ps[j]).len()<=r*E)continue;
			o=(ps[i]+ps[j])/2;
			r=(o-ps[i]).len();
			for(int k=0;k<j;k++){
				if((o-ps[k]).len()<=r*E)continue;
				o=ccCenter(ps[i],ps[j],ps[k]);
				r=(o-ps[i]).len();
			}
		}
	}
	return {o,r};
}
