#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/HashMap.h"

mt19937_64 rng(5);

int main(){
	long long checks=0;
	for(int it=0;it<200;it++){
		h.clear();
		map<ll,int>b;
		vector<ll>keys;
		for(int i=0;i<50;i++)keys.push_back(it%3==0?(ll)(rng()%1000)<<32:it%3==1?(ll)rng():(ll)(rng()%41)-20);
		for(int step=0;step<3000;step++){
			ll k=keys[rng()%keys.size()];
			int c=rng()%4,v=(int)(rng()%1000);
			if(c==0)h[k]=v,b[k]=v;
			else if(c==1)h.erase(k),b.erase(k);
			else if(c==2){
				bool in=h.find(k)!=h.end();
				assert(in==b.count(k));
				if(in)assert(h.find(k)->second==b[k]);
				checks++;
			}else{
				assert(h.size()==b.size());
				map<ll,int>m;
				for(auto [x,y]:h)m[x]=y;
				assert(m==b);checks++;
			}
		}
	}
	// many keys
	h.clear();
	for(ll i=0;i<1000000;i++)h[i*1000003]+=(int)i;
	for(ll i=0;i<1000000;i++)assert(h[i*1000003]==(int)i),checks++;
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
