#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/UnionFindRollback.h"

mt19937 rng(3);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

// brute: component labels
struct Brute{
	vector<int>c;
	Brute(int n=0):c(n+1){iota(c.begin(),c.end(),0);}
	bool join(int x,int y){
		int a=c[x],b=c[y];if(a==b)return 0;
		for(int&v:c)if(v==a)v=b;
		return 1;
	}
	int size(int x){return (int)count(c.begin(),c.end(),c[x]);}
};

int main(){
	long long checks=0;
	// plain DSU, reused across tests
	for(int it=0;it<2000;it++){
		int n=rnd(1,40);
		dsu.init(n);Brute b(n);
		for(int s=0;s<100;s++){
			int x=rnd(1,n),y=rnd(1,n);
			if(rng()%2)assert(dsu.unite(x,y)==b.join(x,y));
			else assert((dsu.find(x)==dsu.find(y))==(b.c[x]==b.c[y])),checks++;
		}
	}
	// rollback DSU
	for(int it=0;it<2000;it++){
		int n=rnd(1,40);
		rdsu.init(n);
		vector<pair<int,Brute>>hist; // (time, state)
		Brute b(n);
		for(int s=0;s<150;s++){
			int c=rng()%5;
			if(c<2){
				int x=rnd(1,n),y=rnd(1,n);
				assert(rdsu.unite(x,y)==b.join(x,y));
			}else if(c==2){
				hist.push_back({rdsu.time(),b});
			}else if(c==3&&!hist.empty()){
				int k=rnd(0,(int)hist.size()-1);
				rdsu.rollback(hist[k].first);
				b=hist[k].second;
				hist.resize(k);
			}else{
				int x=rnd(1,n),y=rnd(1,n);
				assert((rdsu.find(x)==rdsu.find(y))==(b.c[x]==b.c[y]));
				assert(rdsu.siz[rdsu.find(x)]==b.size(x));
				checks++;
			}
		}
	}
	// large: chain unions, depth stays logarithmic
	int n=200000;
	rdsu.init(n);dsu.init(n);
	for(int i=1;i<n;i++)rdsu.unite(i,i+1),dsu.unite(i,i+1);
	assert(rdsu.siz[rdsu.find(1)]==n&&dsu.find(1)==dsu.find(n));
	rdsu.rollback(0);
	for(int i=1;i<=n;i++)assert(rdsu.find(i)==i&&rdsu.siz[i]==1);
	checks++;
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
