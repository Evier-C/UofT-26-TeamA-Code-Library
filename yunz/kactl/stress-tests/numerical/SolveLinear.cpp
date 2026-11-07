#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/SolveLinear.h"

mt19937 rng(10);
const ll P=1000000007;
ll pw(ll b,ll e){ll r=1;for(b%=P;e;e>>=1,b=b*b%P)if(e&1)r=r*b%P;return r;}
// 模大素数求秩 (元素很小, 子式不会是 P 的倍数, 所以等于有理数域上的秩)
int rankMod(vector<vector<ll>> m){
	int n=m.size(),k=n?m[0].size():0,r=0;
	for(auto&row:m)for(auto&v:row)v=(v%P+P)%P;
	for(int c=0;c<k&&r<n;c++){
		int p=-1;
		for(int i=r;i<n;i++)if(m[i][c]){p=i;break;}
		if(p<0)continue;
		swap(m[p],m[r]);
		ll iv=pw(m[r][c],P-2);
		for(int i=0;i<n;i++)if(i!=r&&m[i][c]){
			ll t=m[i][c]*iv%P;
			for(int j=0;j<k;j++)m[i][j]=(m[i][j]-t*m[r][j]%P+P)%P;
		}
		r++;
	}
	return r;
}
int main(){
	long long checks=0;
	int cnt[3]={0,0,0};
	for(int it=0;it<30000;it++){
		int n=rng()%6+1,m=rng()%6+1;
		vector<vector<ll>> A(n,vector<ll>(m)),Ab(n,vector<ll>(m+1));
		vector<ll> b(n);
		for(auto&r:A)for(auto&v:r)v=(int)(rng()%7)-3;
		// 让一些行是其他行的线性组合
		for(int i=0;i<n;i++)if(i>0&&rng()%3==0){
			int u=rng()%i,w=rng()%i,cu=(int)(rng()%3)-1,cw=(int)(rng()%3)-1;
			for(int j=0;j<m;j++)A[i][j]=cu*A[u][j]+cw*A[w][j];
		}
		vector<ll> x0(m);
		for(auto&v:x0)v=(int)(rng()%7)-3;
		for(int i=0;i<n;i++){
			b[i]=0;
			for(int j=0;j<m;j++)b[i]+=A[i][j]*x0[j];
			if(rng()%4==0)b[i]+=(int)(rng()%3)-1; // 可能无解
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)Ab[i][j]=A[i][j];
			Ab[i][m]=b[i];
		}
		int rA=rankMod(A),rAb=rankMod(Ab);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)a[i][j]=A[i-1][j-1];
			a[i][m+1]=b[i-1];
		}
		int r=gauss(n,m);
		if(rAb>rA){
			assert(r==-1);cnt[0]++;
		}else{
			assert(r==rA);
			if(r<m)cnt[1]++;else cnt[2]++;
			for(int i=0;i<n;i++){
				double s=0;
				for(int j=0;j<m;j++)s+=A[i][j]*x[j+1];
				assert(fabs(s-b[i])<1e-7);
			}
		}
		checks++;
	}
	assert(cnt[0]>1000&&cnt[1]>1000&&cnt[2]>1000);
	// 大规模随机 (几乎必有唯一解)
	for(int it=0;it<20;it++){
		int n=rng()%300+1;
		vector<vector<double>> A(n,vector<double>(n));
		vector<double> b(n);
		for(auto&r:A)for(auto&v:r)v=(rng()%20001)/1000.0-10;
		for(auto&v:b)v=(rng()%20001)/1000.0-10;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)a[i][j]=A[i-1][j-1];
			a[i][n+1]=b[i-1];
		}
		assert(gauss(n,n)==n);
		for(int i=0;i<n;i++){
			double s=0;
			for(int j=0;j<n;j++)s+=A[i][j]*x[j+1];
			assert(fabs(s-b[i])<1e-6);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
