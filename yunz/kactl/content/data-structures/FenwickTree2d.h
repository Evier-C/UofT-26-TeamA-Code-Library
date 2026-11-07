/**
 * Description: 二维树状数组 BIT2D, 全局对象 bit2, 矩阵 a[1..n][1..m].
 * init(n, m): 设行数列数并清空. add(x, y, v): a[x][y] 加 v.
 * ask(x, y): 子矩阵 [1..x][1..y] 的和.
 * query(x1, y1, x2, y2): 子矩阵 [x1..x2][y1..y2] 的和, 要求 x1 不超过 x2,
 * y1 不超过 y2.
 * 注意: 内存为 $N \cdot M$ 个 ll, 默认 1005 * 1005 约 8MB, 对象要定义在全局;
 * 要第二个就在全局再写 BIT2D bit3; 多组数据重新 init.
 * 坐标很大但修改点事先已知时, 改用离线: 离散化 + 一维树状数组扫描线.
 * Usage: bit2.init(n, m); // 每组数据先 init
 * bit2.add(x, y, v); // a[x][y] += v
 * ll s = bit2.query(x1, y1, x2, y2); // 子矩阵和
 * Time: 每次操作 O(\log N \log M)
 */
#pragma once

struct BIT2D{
	static const int N=1005,M=1005;
	int n,m;
	ll c[N][M];
	void init(int _n,int _m){
		n=_n;
		m=_m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)c[i][j]=0;
		}
	}
	void add(int x,int y,ll v){
		for(int i=x;i<=n;i+=i&-i){
			for(int j=y;j<=m;j+=j&-j)c[i][j]+=v;
		}
	}
	ll ask(int x,int y){ // [1..x][1..y] 的和
		ll r=0;
		for(int i=x;i;i-=i&-i){
			for(int j=y;j;j-=j&-j)r+=c[i][j];
		}
		return r;
	}
	ll query(int x1,int y1,int x2,int y2){
		ll s=ask(x2,y2)-ask(x1-1,y2);
		s-=ask(x2,y1-1);
		s+=ask(x1-1,y1-1);
		return s;
	}
}bit2;
