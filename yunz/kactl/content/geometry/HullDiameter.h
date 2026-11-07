/**
 * Description: 旋转卡壳求凸包直径 (点集中距离最远的两点), 返回最远距离的平方.
 * 输入为逆时针凸包 (无重复点和共线点, 即 convexHull 的结果), 可以只有 1 或 2 个点.
 * 求原始点集的最远点对时先求凸包. T 为 ll 时结果精确, 坐标约 $10^9$ 以内.
 * Usage: vector<Point> h=convexHull(pts);
 * T d2=hullDiameter(h); // 直径的平方
 * double d=sqrt((double)d2); // 直径
 * Time: O(n)
 */
#pragma once

#include "Point.h"

T hullDiameter(vector<Point>&h){
	int n=h.size();
	if(n==1)return 0;
	if(n==2)return (h[0]-h[1]).len2();
	T res=0;
	int j=1;
	for(int i=0;i<n;i++){
		Point a=h[i],b=h[(i+1)%n];
		// h[j+1] 离边 ab 更远时移动 j
		while(sgn((b-a).cross(h[(j+1)%n]-h[j]))>0)j=(j+1)%n;
		res=max(res,(a-h[j]).len2());
		res=max(res,(b-h[j]).len2());
	}
	return res;
}
