#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/MoQueries.h"

mt19937 rng(5);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		bool big=it>=2995;
		n=big?rnd(50000,200000):rnd(1,40);
		q=big?rnd(50000,200000):rnd(1,40);
		int V=big?n:rnd(1,n);
		for(int i=1;i<=n;i++)a[i]=rnd(1,V);
		vector<array<int,2>>Q(q+1);
		for(int i=1;i<=q;i++){
			int l=rnd(1,n),r=rnd(l,n);
			if(big&&rng()%100)r=min(n,l+rnd(0,40));
			qs[i]={l,r,i};Q[i]={l,r};
		}
		memset(cnt,0,sizeof cnt);cur=0; // multi-test clear
		solve();
		for(int i=1;i<=q;i++){
			if(big&&Q[i][1]-Q[i][0]>40&&i%50)continue;
			set<int>s(a+Q[i][0],a+Q[i][1]+1);
			assert(ans[i]==(ll)s.size());checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
