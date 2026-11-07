/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-07
 * License: CC0
 * Source: My geometric reasoning
 * Description: 返回半径为 radius 的球面上两点间的最短 (球面) 距离. 两点的方位角 (经度)
 * 为 f1 ($\phi_1$) 和 f2 ($\phi_2$), 从 x 轴量起; 天顶角 (纬度) 为 t1 ($\theta_1$) 和
 * t2 ($\theta_2$), 从 z 轴量起 (0 为北极). 角度均为弧度. 算法先把球坐标转为直角坐标,
 * 若已有直角坐标, 只需用最后两行. 此时 dx*radius 为两点在 x 方向上的差,
 * d*radius 为两点间的直线距离.
 * Usage:
 * 	double d = sphericalDistance(f1, t1, f2, t2, radius);
 * Status: tested on kattis:airlinehub
 */
#pragma once

double sphericalDistance(double f1,double t1,
		double f2,double t2,double radius){
	double dx=sin(t2)*cos(f2)-sin(t1)*cos(f1);
	double dy=sin(t2)*sin(f2)-sin(t1)*sin(f1);
	double dz=cos(t2)-cos(t1);
	double d=sqrt(dx*dx+dy*dy+dz*dz);
	return radius*2*asin(d/2);
}
