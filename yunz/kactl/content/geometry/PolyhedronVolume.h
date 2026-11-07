/**
 * Author: Mattias de Zalenski
 * Date: 2002-11-04
 * Description: 求多面体 (有向) 体积的神奇公式. 各面须朝外.
 * trilist 的元素需有下标成员 a, b, c, 如 3dHull 的 F.
 * Usage:
 * 	double vol = signedPolyVolume(pts, hull3d(pts));
 * Status: tested
 */
#pragma once

template<class V, class L>
double signedPolyVolume(const V& p, const L& trilist) {
	double v = 0;
	for (auto i : trilist) v += p[i.a].cross(p[i.b]).dot(p[i.c]);
	return v / 6;
}
