/**
 * Description: 最小圆覆盖 (随机增量法): 求半径最小的圆, 使所有点都在圆内或圆上.
 * 输入点集 vector<Point> (下标 0..n-1, 至少 1 个点, 可有重复点和共线点),
 * 返回 \{圆心, 半径\}. 要求 T 为 double. 判断点在圆外时用相对误差 1e-8.
 * 函数内部会打乱点的顺序 (传值, 不影响原数组).
 * Usage: vector<Point> ps={Point(0,0),Point(2,0),Point(1,1)};
 * pair<Point,double> c=mec(ps);
 * // 圆心 c.first=(1,0), 半径 c.second=1
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
