#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/number-theory/FastEratosthenes.h"

int main(){
	ll checks=0;
	int n=1000000;
	sieve(n);
	assert(cnt==78498);
	for(int i=1;i<cnt;i++)assert(pri[i]<pri[i+1]);
	for(int x=1;x<=200000;x++){
		int y=x,ph=x,m=1;bool pr=x>=2;
		for(int p=2;p*p<=y;p++)if(y%p==0){
			pr=0;int e=0;
			while(y%p==0)y/=p,e++;
			ph=ph/p*(p-1),m=e>1?0:-m;
		}
		if(y>1)ph=ph/y*(y-1),m=-m,pr=pr&&y==x;
		assert(phi[x]==ph&&mu[x]==m);
		if(x>=2)assert((!vis[x])==pr);
		checks++;
	}
	for(int x=200001;x<=n;x++){ // 检查质数和积性
		int p=2;
		while(p*p<=x&&x%p)p++;
		bool pr=p*p>x;
		assert((!vis[x])==pr);checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
