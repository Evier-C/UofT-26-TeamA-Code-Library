/**
 * Description: 旋转卡壳 (双指针) 求凸包直径 (点集中距离最远的两点), 返回最远距离的平方.
 * 输入为逆时针凸包 (无重复点和共线点, 即 convexHull 的结果), 可以只有 1 或 2 个点.
 * 求原始点集的最远点对时先求凸包. T 为 ll 时结果精确, 坐标约 $10^9$ 以内.
 * 循环中对每条边 $ab$ ($a = h_i, b = h_{i+1}$), $j$ 单调移动到离直线 $ab$ 最远的点 (叉积 $(b-a) \times (h_j - a)$ 最大).
 * countDiameter 返回距离等于直径的点对个数: 在同一循环中收集所有对踵点对 (边的两端与 $h_j$,
 * 边与 $h_j h_{j+1}$ 平行时再加上 $h_{j+1}$), 用 set 去重后统计距离平方等于直径平方的对.
 * 统计的是凸包顶点 (即去掉重复点后的不同点) 之间的无序对; 直径的端点一定是凸包顶点,
 * 所以等于原点集中不同点的直径对数. 只有 1 个点时为 0.
 * 同一个循环的改法 (都只改每步更新的量):
 * (a) 凸包最小宽度: 每条边求出 $j$ 后, 用 $h_j$ 到直线 $ab$ 的距离 $|(b-a) \times (h_j - a)| / |b-a|$ 更新答案取 min.
 * (b) 最小面积 / 最小周长外接矩形 (矩形一边必在某条边上): 再维护两个单调指针, $k$ 为点积 $(b-a) \cdot h_k$ 最大的点
 * ($i=0$ 时从 1 开始, 下一个点积更大就前移), $l$ 为点积最小的点 ($i=0$ 时从 $j$ 开始, 下一个点积更小就前移).
 * 宽 $= |(b-a) \times (h_j - a)| / |b-a|$, 长 $= (b-a) \cdot (h_k - h_l) / |b-a|$, 用 宽 $\times$ 长 (或 2(宽+长)) 更新 min.
 * (c) 两个凸包 $P, Q$ 间的最远 / 最近距离: 等价于 Minkowski 和 $P + (-Q)$ (逆时针按极角归并两者的边) 的顶点到原点的最大距离 /
 * 原点到该凸多边形的距离 (原点在内部则相交, 为 0); 归并时的每个顶点就是一对 $P$ 沿方向 $d$ 最远点与 $Q$ 沿 $-d$ 最远点 (对踵点对).
 * Usage: vector<Point> h=convexHull(pts);
 * T d2=hullDiameter(h); // 直径的平方
 * double d=sqrt((double)d2); // 直径
 * int c=countDiameter(h); // 距离等于直径的点对数
 * Time: O(n), countDiameter 为 O(n \log n)
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
// 距离等于直径的点对个数, 统计凸包顶点的无序对
int countDiameter(vector<Point>&h){
	int n=h.size();
	if(n<=1)return 0;
	if(n==2)return 1;
	T best=hullDiameter(h);
	set<pair<int,int>>s; // 下标对, 小的在前, 用于去重
	int j=1;
	for(int i=0;i<n;i++){
		int i2=(i+1)%n;
		Point a=h[i],b=h[i2];
		while(sgn((b-a).cross(h[(j+1)%n]-h[j]))>0)j=(j+1)%n;
		int j2=(j+1)%n;
		vector<int>c={j}; // 对踵点
		// 边 h[j]h[j+1] 与 ab 平行时 h[j+1] 也是对踵点
		if(sgn((b-a).cross(h[j2]-h[j]))==0)c.push_back(j2);
		for(int k:c){
			for(int u:{i,i2}){
				if(sgn((h[u]-h[k]).len2()-best)==0){
					s.insert({min(u,k),max(u,k)});
				}
			}
		}
	}
	return s.size();
}
