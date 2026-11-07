/**
 * Description:
\\\begin{minipage}{75mm}
Andrew 单调链求凸包. 输入点集 vector<Point> (可有重复点, 共线点),
返回凸包顶点, 逆时针, 下标 0..m-1, 从最左 (x 最小, 再 y 最小) 的点开始.
不保留共线点 (凸包边上的点不算顶点), 重复点只算一次.
所有点重合时返回 1 个点, 全部共线时返回 2 个端点. T 可为 ll (结果精确).
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Usage: vector<Point> pts; // pts[0..n-1]
 * for(int i=0;i<n;i++)pts.push_back(Point(x[i],y[i]));
 * vector<Point> h=convexHull(pts); // h[0..m-1] 逆时针
 * int m=h.size(); // 边为 h[i] 到 h[(i+1)\%m]
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

vector<Point>convexHull(vector<Point>p){
	sort(p.begin(),p.end());
	p.erase(unique(p.begin(),p.end()),p.end());
	int n=p.size(),k=0;
	if(n<=1)return p;
	vector<Point>h(2*n);
	// 要保留共线点, 两处改成严格小于 0, 全部共线时要特判
	for(int i=0;i<n;i++){ // 下凸壳
		while(k>=2&&sgn(cross(h[k-2],h[k-1],p[i]))<=0)k--;
		h[k]=p[i];
		k++;
	}
	int lo=k;
	for(int i=n-2;i>=0;i--){ // 上凸壳
		while(k>lo&&sgn(cross(h[k-2],h[k-1],p[i]))<=0)k--;
		h[k]=p[i];
		k++;
	}
	h.resize(k-1); // 最后一个点是 p[0], 去掉
	return h;
}
