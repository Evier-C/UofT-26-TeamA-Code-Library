/**
 * Description: 二维树状数组, 矩阵 a[1..n][1..m]. 内存 $N \cdot M$ 个 ll, 默认约 8MB,
 * 对象要定义在全局.
 * Usage: bit2.init(n, m); // 每组数据先 init
 * bit2.add(x, y, v); // a[x][y] += v
 * ll p = bit2.ask(x, y); // 子矩阵 [1..x][1..y] 的和
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
