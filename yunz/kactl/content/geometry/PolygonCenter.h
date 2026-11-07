/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: 返回多边形的重心 (质心).
 * Usage:
 * 	P c = polygonCenter(v);
 * Time: O(n)
 * Status: Tested
 */
#pragma once

#include "Point.h"

typedef Point<double>P;
P polygonCenter(const vector<P>&v){
	P res(0,0);double A=0;
	for(int i=0,j=sz(v)-1;i<sz(v);j=i++){
		res=res+(v[i]+v[j])*v[j].cross(v[i]);
		A+=v[j].cross(v[i]);
	}
	return res/A/3;
}
