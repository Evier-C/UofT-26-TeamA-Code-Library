/**
 * Description: 直线与凸多边形求交. 多边形 poly 须为逆时针且无共线点 (如 convexHull 的结果), 下标 0..n-1.
 * lineHull(a, b, poly) 返回一对下标, 描述直线 ab ($a \neq b$) 与多边形的相交情况:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ 不相交,
 *    \item $(i, -1)$ 只碰到顶点 $i$,
 *    \item $(i, i)$ 沿着边 $(i, i+1)$,
 *    \item $(i, j)$ 穿过边 $(i, i+1)$ 和 $(j, j+1)$.
 *  \end{itemize*}
 *  最后一种情形中若穿过顶点 $i$, 视为发生在边 $(i, i+1)$ 上.
 *  返回顺序与沿 a 到 b 方向依次碰到多边形的顺序一致. 下标 $i+1$ 按模 n 计算.
 * \texttt{extrVertex(poly, dir)} 返回在方向 dir 上投影最大 (最远) 的顶点下标.
 * 只用到叉积符号, T 为 ll 时结果精确.
 * Usage: vector<Point> poly=convexHull(pts);
 * array<int,2> r=lineHull(a,b,poly);
 * if(r[0]==-1){} // 不相交
 * else if(r[1]==-1){} // 只碰到顶点 r[0]
 * else if(r[0]==r[1]){} // 沿着边 r[0]
 * else{} // 穿过边 r[0] 和边 r[1]
 * int i=extrVertex(poly,Point(1,0)); // x 最大的顶点
 * Time: O(\log n)
 */
#pragma once

#include "Point.h"

int extrVertex(vector<Point>&poly,Point dir){
	int n=poly.size(),lo=0,hi=n;
	// 比较顶点 i 和 j 在 dir 上的投影, j 更远时为 1
	auto cmp=[&](int i,int j){
		return sgn(cross(perp(dir),poly[i%n]-poly[j%n]));
	};
	// i 是否为最远点
	auto extr=[&](int i){
		return cmp(i+1,i)>=0&&cmp(i,i-1+n)<0;
	};
	if(extr(0))return 0;
	while(lo+1<hi){
		int m=(lo+hi)/2;
		if(extr(m))return m;
		int ls=cmp(lo+1,lo),ms=cmp(m+1,m);
		if(ls<ms||(ls==ms&&ls==cmp(lo,m)))hi=m;
		else lo=m;
	}
	return lo;
}
array<int,2>lineHull(Point a,Point b,vector<Point>&poly){
	int n=poly.size();
	// 顶点 i 在直线 ab 的哪一侧
	auto cmpL=[&](int i){
		return sgn(cross(a,poly[i],b));
	};
	int endA=extrVertex(poly,perp(a-b));
	int endB=extrVertex(poly,perp(b-a));
	if(cmpL(endA)<0||cmpL(endB)>0)return {-1,-1};
	array<int,2>res;
	for(int i=0;i<2;i++){
		int lo=endB,hi=endA;
		while((lo+1)%n!=hi){
			int m=((lo+hi+(lo<hi?0:n))/2)%n;
			if(cmpL(m)==cmpL(endB))lo=m;
			else hi=m;
		}
		res[i]=(lo+!cmpL(hi))%n;
		swap(endA,endB);
	}
	if(res[0]==res[1])return {res[0],-1};
	if(!cmpL(res[0])&&!cmpL(res[1])){
		switch((res[0]-res[1]+n+1)%n){
			case 0:return {res[0],res[0]};
			case 2:return {res[1],res[1]};
		}
	}
	return res;
}
