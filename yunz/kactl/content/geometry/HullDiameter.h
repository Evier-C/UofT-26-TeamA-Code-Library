/**
 * Description: 旋转卡壳求凸包直径 (最远点对), 返回距离的平方.
 * 输入为逆时针凸包 (无重复点和共线点, 如 convexHull 的结果).
 * Usage: vector<Point> h=convexHull(pts);
 * T d2=hullDiameter(h); // 直径为 sqrt(d2)
 * Time: O(n)
 */
#pragma once

#include "Point.h"

T hullDiameter(vector<Point>&h){
	int n=h.size();
	if(n<=2)return n==2?len2(h[0]-h[1]):0;
	T res=0;
	for(int i=0,j=1;i<n;i++){
		Point a=h[i],b=h[(i+1)%n];
		// h[j+1] 离边 ab 更远时移动 j
		while(sgn(cross(b-a,h[(j+1)%n]-h[j]))>0)j=(j+1)%n;
		res=max(res,max(len2(a-h[j]),len2(b-h[j])));
	}
	return res;
}
