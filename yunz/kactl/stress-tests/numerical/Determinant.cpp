#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/Determinant.h"

mt19937 rng(8);
// 按定义 (枚举排列) 求行列式
double leibniz(vector<vector<double>>&m){
	int n=m.size();
	vector<int> p(n);
	iota(p.begin(),p.end(),0);
	double res=0;
	do{
		int inv=0;
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(p[i]>p[j])inv++;
		double t=inv&1?-1:1;
		for(int i=0;i<n;i++)t*=m[i][p[i]];
		res+=t;
	}while(next_permutation(p.begin(),p.end()));
	return res;
}
int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		int n=rng()%7+1;
		vector<vector<double>> m(n,vector<double>(n));
		int R=rng()%3==0?1:5;
		for(auto&r:m)for(auto&v:r)v=(int)(rng()%(2*R+1))-R;
		if(n>1&&rng()%4==0)m[rng()%n]=m[rng()%n]; // 可能奇异
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=m[i-1][j-1];
		double want=leibniz(m),got=det(n);
		assert(fabs(want-got)<1e-6*max(1.0,fabs(want)));
		checks++;
	}
	// 大矩阵: 与 long double 高斯消元比较
	for(int it=0;it<50;it++){
		int n=rng()%200+1;
		vector<vector<long double>> m(n,vector<long double>(n));
		for(int i=0;i<n;i++)for(int j=0;j<n;j++){
			m[i][j]=(rng()%2001)/1000.0-1; // 防止溢出
			a[i+1][j+1]=(double)m[i][j];
		}
		long double want=1;
		for(int i=0;i<n;i++){
			int p=i;
			for(int j=i;j<n;j++)if(fabsl(m[j][i])>fabsl(m[p][i]))p=j;
			if(p!=i)swap(m[p],m[i]),want=-want;
			want*=m[i][i];
			for(int j=i+1;j<n;j++){
				long double t=m[j][i]/m[i][i];
				for(int k=i;k<n;k++)m[j][k]-=t*m[i][k];
			}
		}
		double got=det(n);
		assert(fabsl(got-want)<1e-6*fabsl(want));
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
