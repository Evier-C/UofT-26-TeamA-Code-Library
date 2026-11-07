#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/LeftistHeap.h"

mt19937 rng(17);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		bool big=it>=2995;
		int n=big?100000:rnd(1,30);
		int V=big?1000000000:rnd(1,10);
		lh.init(); // multi-test
		vector<ll>a(n+1);
		vector<int>grp(n+1);
		vector<char>dead(n+1,0);
		vector<set<pair<ll,int>>>S(n+1);
		for(int i=1;i<=n;i++){
			a[i]=rnd(0,V);
			assert(lh.newnode(a[i])==i);
			grp[i]=i;
			S[i].insert({a[i],i});
		}
		int ops=big?200000:200;
		for(int s=0;s<ops;s++){
			int x=rnd(1,n),y=rnd(1,n);
			if(rng()%2){
				lh.join(x,y);
				if(!dead[x]&&!dead[y]&&grp[x]!=grp[y]){
					int gx=grp[x],gy=grp[y];
					if(S[gx].size()<S[gy].size())swap(gx,gy);
					for(auto [v,i]:S[gy]){
						S[gx].insert({v,i});
						grp[i]=gx;
					}
					S[gy].clear();
				}
			}else{
				assert((bool)lh.del[x]==(bool)dead[x]);
				if(dead[x])continue;
				auto [v,i]=*S[grp[x]].begin();
				assert(lh.top(x)==v);
				assert(lh.find(x)==i);
				lh.pop(x);
				S[grp[x]].erase(S[grp[x]].begin());
				dead[i]=1;
				checks++;
			}
		}
		for(int i=1;i<=n;i++){
			assert((bool)lh.del[i]==(bool)dead[i]);
			if(!dead[i]&&(!big||i%100==0)){
				assert(lh.find(i)==S[grp[i]].begin()->second);
				checks++;
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
