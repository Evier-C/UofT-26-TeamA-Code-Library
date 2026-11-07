/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
返回点 p 到直线 ab 的有向距离. 从 a 看向 b, 左侧为正, 右侧为负; a==b 时得 nan.
P 可为 Point<T> 或 Point3D<T>, T 如 double 或 long long.
中间有乘积, 用 int 或 long long 时注意溢出.
Point3D 总得非负距离; 对 Point3D 需对叉积结果调用 .dist.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Usage:
 * 	double d = lineDist(a, b, p); // 正数表示 p 在左侧
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
