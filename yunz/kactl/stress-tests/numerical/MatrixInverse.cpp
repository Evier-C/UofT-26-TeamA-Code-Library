#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/MatrixInverse.h"

mt19937 rng(12);
const ll P=1000000007;
ll pw(ll b,ll e){ll r=1;for(b%=P;e;e>>=1,b=b*b%P)if(e&1)r=r*b%P;return r;}
bool singular(vector<vector<ll>> m){ // 元素很小, 模大素数判奇异是精确的
	int n=m.size();
	for(auto&r:m)for(auto&v:r)v=(v%P+P)%P;
	for(int i=0;i<n;i++){
		int q=-1;
		for(int j=i;j<n;j++)if(m[j][i]){q=j;break;}
		if(q<0)return true;
		swap(m[q],m[i]);
		ll iv=pw(m[i][i],P-2);
		for(int j=i+1;j<n;j++){
			ll t=m[j][i]*iv%P;
			for(int k=i;k<n;k++)m[j][k]=(m[j][k]-t*m[i][k]%P+P)%P;
		}
	}
	return false;
}
int main(){
	long long checks=0;
	int cnt[2]={0,0};
	for(int it=0;it<30000;it++){
		int n=rng()%6+1;
		vector<vector<ll>> m(n,vector<ll>(n));
		int R=rng()%2?1:4;
		for(auto&r:m)for(auto&v:r)v=(int)(rng()%(2*R+1))-R;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=m[i-1][j-1];
		bool ok=inverse(n);
		assert(ok==!singular(m));
		cnt[ok]++;
		if(ok){
			for(int i=0;i<n;i++)for(int j=0;j<n;j++){
				double s=0;
				for(int k=0;k<n;k++)s+=m[i][k]*a[k+1][j+1];
				assert(fabs(s-(i==j))<1e-8);
			}
		}
		checks++;
	}
	assert(cnt[0]>1000&&cnt[1]>1000);
	for(int it=0;it<20;it++){
		int n=rng()%300+1;
		vector<vector<double>> m(n,vector<double>(n));
		for(auto&r:m)for(auto&v:r)v=(rng()%20001)/1000.0-10;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=m[i-1][j-1];
		assert(inverse(n));
		for(int i=0;i<n;i++)for(int j=0;j<n;j++){
			double s=0;
			for(int k=0;k<n;k++)s+=m[i][k]*a[k+1][j+1];
			assert(fabs(s-(i==j))<1e-7);
		}
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
