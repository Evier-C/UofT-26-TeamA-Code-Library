#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/SolveLinearBinary.h"

mt19937 rng(11);
int main(){
	long long checks=0;
	for(int it=0;it<30000;it++){
		int n=rng()%8+1,m=rng()%10+1;
		vector<vector<int>> A(n,vector<int>(m));
		vector<int> b(n);
		for(auto&r:A)for(auto&v:r)v=rng()%(rng()%3==0?4:2)==1;
		for(int i=1;i<n;i++)if(rng()%3==0){ // 线性相关的行
			int u=rng()%i;
			for(int j=0;j<m;j++)A[i][j]^=A[u][j];
		}
		for(auto&v:b)v=rng()%2;
		for(int i=1;i<=n;i++){ // 按 Usage 清空再填
			a[i].reset();
			for(int j=1;j<=m;j++)if(A[i-1][j-1])a[i][j]=1;
			a[i][m+1]=b[i-1];
		}
		int r=gaussXor(n,m);
		// 暴力枚举所有 x 数解的个数
		int sol=0;
		for(int mask=0;mask<(1<<m);mask++){
			bool ok=true;
			for(int i=0;i<n&&ok;i++){
				int s=0;
				for(int j=0;j<m;j++)if(mask>>j&1)s^=A[i][j];
				if(s!=b[i])ok=false;
			}
			sol+=ok;
		}
		if(sol==0)assert(r==-1);
		else{
			assert(r>=0&&sol==(1<<(m-r)));
			for(int i=0;i<n;i++){
				int s=0;
				for(int j=0;j<m;j++)s^=A[i][j]&x[j+1];
				assert(s==b[i]);
			}
		}
		checks++;
	}
	// 大规模: 构造有解的方程组, 检查解
	for(int it=0;it<20;it++){
		int n=rng()%900+1,m=rng()%900+1;
		vector<int> x0(m);
		for(auto&v:x0)v=rng()%2;
		vector<vector<int>> A(n,vector<int>(m));
		vector<int> b(n);
		for(int i=1;i<=n;i++){
			a[i].reset();
			int s=0;
			for(int j=1;j<=m;j++){
				A[i-1][j-1]=rng()%2;
				if(A[i-1][j-1])a[i][j]=1,s^=x0[j-1];
			}
			b[i-1]=s;a[i][m+1]=s;
		}
		int r=gaussXor(n,m);
		assert(r>=0&&r<=min(n,m));
		for(int i=0;i<n;i++){
			int s=0;
			for(int j=0;j<m;j++)s^=A[i][j]&x[j+1];
			assert(s==b[i]);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
