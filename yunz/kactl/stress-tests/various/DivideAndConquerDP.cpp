#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/DivideAndConquerDP.h"

ll h[105][105];
int main(){
	mt19937_64 rng(16);
	ll checks=0;
	for(int it=0;it<20000;it++){
		int n=rng()%(it<15000?12:80)+1,m=rng()%n+1;
		for(int i=1;i<=n;i++)s[i]=s[i-1]+(ll)(rng()%(it%2?5:1000000));
		ll ans=solveDP(n,m);
		const ll INF=LLONG_MAX/4;
		for(int j=0;j<=m;j++)for(int i=0;i<=n;i++)h[j][i]=INF;
		h[0][0]=0;
		for(int j=1;j<=m;j++)for(int i=1;i<=n;i++)
			for(int k=0;k<i;k++)if(h[j-1][k]<INF)
				h[j][i]=min(h[j][i],h[j-1][k]+w(k+1,i));
		assert(ans==h[m][n]);checks++;
	}
	int n=100000;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(ll)(rng()%10000);
	ll ans=solveDP(n,20);
	assert(ans>0);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
