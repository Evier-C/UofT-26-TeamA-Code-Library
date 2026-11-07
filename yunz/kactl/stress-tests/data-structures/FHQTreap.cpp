#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/FHQTreap.h"

mt19937 rng2(3);
int rd(int lo,int hi){return lo+(int)(rng2()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	// mode 1: ordered multiset
	for(int it=0;it<2000;it++){
		tot=root=0;
		multiset<ll>ms;
		int V=rd(1,30);
		for(int s=0;s<200;s++){
			int op=rd(0,5);
			ll v=rd(-V,V);
			if(op<=1)insert(v),ms.insert(v);
			else if(op==2){
				erase(v);
				auto f=ms.find(v);
				if(f!=ms.end())ms.erase(f);
			}else if(op==3){
				assert(getrank(v)==(int)distance(ms.begin(),ms.lower_bound(v))+1);
			}else if(op==4&&!ms.empty()){
				int k=rd(1,(int)ms.size());
				assert(kth(k)==*next(ms.begin(),k-1));
			}else if(!ms.empty()){
				auto lb=ms.lower_bound(v);
				if(lb!=ms.begin())assert(pre(v)==*prev(lb));
				auto ub=ms.upper_bound(v);
				if(ub!=ms.end())assert(nxt(v)==*ub);
			}
			assert(siz[root]==(int)ms.size());
			checks++;
		}
		vector<ll>o;
		dfs(root,o);
		assert(o==vector<ll>(ms.begin(),ms.end()));
	}
	// mode 2: sequence
	for(int it=0;it<2000;it++){
		tot=root=0;
		int n=rd(1,30);
		vector<ll>a(n+1);
		for(int i=1;i<=n;i++)a[i]=rd(-1000,1000),root=merge(root,newnode(a[i]));
		for(int s=0;s<150;s++){
			int l=rd(1,n),r=rd(l,n);
			if(rng2()%2){
				reverse(l,r);
				std::reverse(a.begin()+l,a.begin()+r+1);
			}else{
				ll e=0;
				for(int i=l;i<=r;i++)e+=a[i];
				assert(rangeSum(l,r)==e);
			}
			checks++;
		}
		vector<ll>o;
		dfs(root,o);
		assert(o==vector<ll>(a.begin()+1,a.end()));
	}
	// large
	tot=root=0;
	multiset<ll>ms;
	for(int i=0;i<200000;i++){
		ll v=rd(0,1000000000);
		insert(v),ms.insert(v);
	}
	for(int q=0;q<1000;q++){
		int k=rd(1,200000);
		assert(kth(k)==*next(ms.begin(),k-1));checks++;
		if(q%100==0){
			ll v=rd(0,1000000000);
			assert(getrank(v)==(int)distance(ms.begin(),ms.lower_bound(v))+1);
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
