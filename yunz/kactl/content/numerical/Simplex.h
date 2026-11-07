/**
 * Description: 单纯形法解线性规划: 在 $Ax \le b$, $x \ge 0$ 下最大化 $c^T x$.
 * 无解返回 -INF, 无界返回 INF, 否则返回最大值, 最优解存在 $x$ 中.
 * 下标从 1 开始: $A[1..m][1..n]$, $b[1..m]$, $c[1..n]$, $x[1..n]$.
 * 求最小化把 $c$ 取负; 约束 $\ge$ 两边乘 -1; 等式拆成两个不等式.
 * 不保证数值稳定. $x = 0$ 可行 (即 $b \ge 0$) 时更快.
 * Usage: m=3,n=2; // 填好 A, b, c, 多组数据重新填即可
 * double v=simplex(m,n); // v 为最大值, 最优解在 x[1..n]
 * if(v==-INF) ... // 无解; v==INF 为无界
 * Time: O(nm \cdot \#pivots), 最坏指数级, 实际很快
 */
#pragma once

const int MM=205,NN=205; // 约束个数, 变量个数上限
const double eps=1e-8,INF=1e18;
double A[MM][NN],b[MM],c[NN],x[NN]; // 输入输出
int m,n,bv[MM],nv[NN]; // 基变量, 非基变量
double D[MM][NN]; // 单纯形表, 下标从 0 开始
bool lessp(double a,int i,double b,int j){
	return make_pair(a,i)<make_pair(b,j);
}
void pivot(int r,int s){
	double inv=1/D[r][s];
	for(int i=0;i<m+2;i++)
		if(i!=r&&fabs(D[i][s])>eps){
			double t=D[i][s]*inv;
			for(int j=0;j<n+2;j++)D[i][j]-=D[r][j]*t;
			D[i][s]=D[r][s]*t;
		}
	for(int j=0;j<n+2;j++)if(j!=s)D[r][j]*=inv;
	for(int i=0;i<m+2;i++)if(i!=r)D[i][s]*=-inv;
	D[r][s]=inv;
	swap(bv[r],nv[s]);
}
bool run(int phase){
	int x=m+phase-1;
	while(1){
		int s=-1; // 入基列 (Bland 规则防循环)
		for(int j=0;j<=n;j++)
			if(nv[j]!=-phase&&(s==-1||
					lessp(D[x][j],nv[j],D[x][s],nv[s])))s=j;
		if(D[x][s]>=-eps)return true;
		int r=-1; // 出基行
		for(int i=0;i<m;i++){
			if(D[i][s]<=eps)continue;
			if(r==-1||lessp(D[i][n+1]/D[i][s],bv[i],
					D[r][n+1]/D[r][s],bv[r]))r=i;
		}
		if(r==-1)return false;
		pivot(r,s);
	}
}
double simplex(int _m,int _n){
	m=_m;n=_n;
	for(int i=0;i<m+2;i++)
		for(int j=0;j<n+2;j++)D[i][j]=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)D[i][j]=A[i+1][j+1];
		bv[i]=n+i;D[i][n]=-1;D[i][n+1]=b[i+1];
	}
	for(int j=0;j<n;j++)nv[j]=j,D[m][j]=-c[j+1];
	nv[n]=-1;D[m+1][n]=1;
	int r=0;
	for(int i=1;i<m;i++)if(D[i][n+1]<D[r][n+1])r=i;
	if(D[r][n+1]<-eps){ // x=0 不可行, 先找可行解
		pivot(r,n);
		if(!run(2)||D[m+1][n+1]<-eps)return -INF;
		for(int i=0;i<m;i++)
			if(bv[i]==-1){
				int s=0;
				for(int j=1;j<=n;j++)
					if(lessp(D[i][j],nv[j],D[i][s],nv[s]))s=j;
				pivot(i,s);
			}
	}
	bool ok=run(1);
	for(int j=1;j<=n;j++)x[j]=0;
	for(int i=0;i<m;i++)
		if(bv[i]<n)x[bv[i]+1]=D[i][n+1];
	return ok?D[m][n+1]:INF;
}
