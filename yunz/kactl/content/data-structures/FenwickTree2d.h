/**
 * Description: 二维树状数组, 矩阵 a[1..n][1..m]: 单点加, 子矩阵求和.
 * 独立使用, 变量名和一维的 FenwickTree.h 相同, 不要同时抄.
 * 坐标很大但修改点事先已知时, 改用离线: 离散化 + 一维树状数组扫描线.
 * Usage: n = ..., m = ...; // 多组数据: 把 c[1..n][1..m] 清 0
 * add(x, y, v); // a[x][y] += v
 * ask(x, y); // 子矩阵 [1..x][1..y] 的和
 * query(x1, y1, x2, y2); // 子矩阵 [x1..x2][y1..y2] 的和
 * Time: O(\log N \log M)
 */
#pragma once

const int N=1005,M=1005;
int n,m;
ll c[N][M];
void add(int x,int y,ll v){
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=m;j+=j&-j)c[i][j]+=v;
}
ll ask(int x,int y){
	ll r=0;
	for(int i=x;i;i-=i&-i)
		for(int j=y;j;j-=j&-j)r+=c[i][j];
	return r;
}
ll query(int x1,int y1,int x2,int y2){
	return ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
}
