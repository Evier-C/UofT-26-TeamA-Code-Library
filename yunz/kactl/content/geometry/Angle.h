/**
 * Description: 精确的极角 (int 向量 $(x,y)$ 再加 $t$ 圈), 用于极角排序和极角扫描.
 * 比较时先比 $t$, 再比 $[0, 2\pi)$ 内的极角, 方向相同视为相等.
 * 坐标绝对值不超过 $10^9$, 向量不能为 $(0,0)$.
 * Usage: vector<Angle> v; // v[0..n-1]
 * for(int i=0;i<n;i++)v.push_back(Angle(x[i],y[i]));
 * sort(v.begin(),v.end()); // 极角排序
 * Angle a=v[0].t90(); // 加 pi/2, 另有 t180, t360
 * Angle d=angleDiff(v[0],v[1]); // 从 v[0] 转到 v[1] 的角
 * Angle s=v[0]+Angle(1,0); // 点加向量, 圈数取最近的
 * // 覆盖线段 pq 的最小角区间, 从 first 逆时针到 second
 * pair<Angle,Angle> r=segmentAngles(Angle(1,2),Angle(3,1));
 * // 双指针: 把每个角加一圈 (t360) 接在后面
 * for(int i=0;i<n;i++)v.push_back(v[i].t360());
 * for(int i=0,j=0;i<n;i++){
 *   while(v[j]<v[i].t180())j++;
 *   // v[i..j-1] 是极角在 [v[i], v[i]+pi) 内的角
 * }
 * Time: 比较 O(1), 排序 O(n \log n)
 */
#pragma once

struct Angle{
	int x,y,t; // 向量 (x,y) 再加 t 圈
	Angle(int x,int y,int t=0):x(x),y(y),t(t){}
	Angle operator-(Angle b)const{return Angle(x-b.x,y-b.y,t);}
	int half()const{ // 角在 [pi, 2pi) 内时为 1
		assert(x||y);
		return y<0||(y==0&&x<0);
	}
	Angle t90()const{return Angle(-y,x,t+(half()&&x>=0));}
	Angle t180()const{return Angle(-x,-y,t+half());}
	Angle t360()const{return Angle(x,y,t+1);}
};
bool operator<(Angle a,Angle b){
	// 末尾再加上长度的平方, 可在极角相同时按长度排序
	return make_tuple(a.t,a.half(),a.y*(ll)b.x)<
		make_tuple(b.t,b.half(),a.x*(ll)b.y);
}
// 覆盖线段 ab 的最小角区间, 从 first 逆时针转到 second
pair<Angle,Angle>segmentAngles(Angle a,Angle b){
	if(b<a)swap(a,b);
	if(b<a.t180())return make_pair(a,b);
	return make_pair(b,a.t360());
}
Angle operator+(Angle a,Angle b){ // 点 a 加向量 b
	Angle r(a.x+b.x,a.y+b.y,a.t);
	if(a.t180()<r)r.t--;
	if(r.t180()<a)return r.t360();
	return r;
}
Angle angleDiff(Angle a,Angle b){ // 角 b 减去角 a
	int tu=b.t-a.t;
	a.t=b.t;
	return Angle(a.x*b.x+a.y*b.y,a.x*b.y-a.y*b.x,tu-(b<a));
}
