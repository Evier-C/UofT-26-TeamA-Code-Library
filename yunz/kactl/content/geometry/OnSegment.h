/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: 当且仅当 p 在线段 se 上时返回 true.
 * 用 Point<double> 时改用 \texttt{(segDist(s,e,p)<=epsilon)}.
 * Usage:
 * 	bool on = onSegment(s, e, p);
 * Status:
 */
#pragma once

#include "Point.h"

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
