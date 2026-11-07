#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/KnuthDP.h"

ll g[205][205];
int main(){
	mt19937_64 rng(15);
	ll checks=0;
	for(int it=0;it<3000;it++){ // 多组数据
		int n=rng()%(it<2500?30:150)+1;
		for(int i=1;i<=n;i++)s[i]=s[i-1]+(ll)(rng()%(it%2?10:1000000));
		ll ans=knuth(n);
		for(int len=1;len<=n;len++)for(int l=1,r=len;r<=n;l++,r++){
			if(l==r){g[l][r]=0;continue;}
			g[l][r]=LLONG_MAX;
			for(int k=l;k<r;k++)g[l][r]=min(g[l][r],g[l][k]+g[k+1][r]+w(l,r));
			assert(f[l][r]==g[l][r]);
		}
		assert(ans==g[1][n]);checks++;
	}
	int n=3000;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(ll)(rng()%1000000000);
	ll ans=knuth(n);
	assert(ans>0);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
