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
		mo.n=big?rnd(50000,200000):rnd(1,40);
		mo.q=big?rnd(50000,200000):rnd(1,40);
		int V=big?mo.n:rnd(1,mo.n);
		for(int i=1;i<=mo.n;i++)mo.a[i]=rnd(1,V);
		vector<array<int,2>>Q(mo.q+1);
		for(int i=1;i<=mo.q;i++){
			int l=rnd(1,mo.n),r=rnd(l,mo.n);
			if(big&&rng()%100)r=min(mo.n,l+rnd(0,40));
			mo.qs[i]={l,r,i};Q[i]={l,r};
		}
		memset(mo.cnt,0,sizeof mo.cnt);mo.cur=0; // multi-test clear
		mo.solve();
		for(int i=1;i<=mo.q;i++){
			if(big&&Q[i][1]-Q[i][0]>40&&i%50)continue;
			set<int>s(mo.a+Q[i][0],mo.a+Q[i][1]+1);
			assert(mo.ans[i]==(ll)s.size());checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
