/**
 * Author: Per Austrin, Ulf Lundstrom
 * Date: 2009-04-09
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 对点 r 施加把直线 p0-p1 变到直线 q0-q1 的线性变换 (平移, 旋转和缩放).
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{content/geometry/linearTransformation}
\vspace{-2mm}
\end{minipage}
 * Usage:
 * 	P r2 = linearTransformation(p0, p1, q0, q1, r);
 * Status: not tested
 */
#pragma once

#include "Point.h"

typedef Point<double>P;
P linearTransformation(const P&p0,const P&p1,
		const P&q0,const P&q1,const P&r){
	P dp=p1-p0,dq=q1-q0,num(dp.cross(dq),dp.dot(dq));
	return q0+P((r-p0).cross(num),(r-p0).dot(num))/dp.dist2();
}
