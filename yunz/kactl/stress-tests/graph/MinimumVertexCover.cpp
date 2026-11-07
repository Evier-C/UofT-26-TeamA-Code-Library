#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/MinimumVertexCover.h"

mt19937 rng(17);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}

long long checks=0;
void test(int nn,int mm,int ne,bool br){
	init(nn,mm);
	vector<pair<int,int>>ed;
	for(int k=0;k<ne;k++){
		int a=rnd(1,nn),b=rnd(1,mm);
		ed.push_back({a,b});g[a].push_back(b);
	}
	vector<int>A,B;
	int k=cover(A,B);
	assert((int)A.size()+(int)B.size()==k);
	vector<int>inA(nn+1),inB(mm+1);
	for(int x:A)assert(1<=x&&x<=nn&&!inA[x]),inA[x]=1;
	for(int x:B)assert(1<=x&&x<=mm&&!inB[x]),inB[x]=1;
	for(auto [a,b]:ed)assert(inA[a]||inB[b]);
	// max independent set: visL true on left, visR false on right
	int isz=0;
	for(int u=1;u<=nn;u++){
		assert(visL[u]==!inA[u]);
		isz+=visL[u];
	}
	for(int v=1;v<=mm;v++){
		assert(visR[v]==(bool)inB[v]);
		isz+=!visR[v];
	}
	for(auto [a,b]:ed)assert(!(visL[a]&&!visR[b]));
	assert(isz==nn+mm-k);
	// complement is an independent set (implied) and k is a matching
	int got=0;
	for(int u=1;u<=nn;u++)if(mL[u])got++;
	assert(got==k);
	if(br){ // brute force minimum vertex cover over all subsets
		int tot=nn+mm,best=tot;
		for(int s=0;s<(1<<tot);s++){
			int c=__builtin_popcount(s);
			if(c>=best)continue;
			bool ok=true;
			for(auto [a,b]:ed)
				if(!(s>>(a-1)&1)&&!(s>>(nn+b-1)&1)){ok=false;break;}
			if(ok)best=c;
		}
		assert(best==k);
	}
	checks++;
}
int main(){
	for(int it=0;it<30000;it++)test(rnd(1,7),rnd(1,7),rnd(0,20),true);
	for(int it=0;it<500;it++)test(rnd(1,300),rnd(1,300),rnd(0,2000),false);
	cout<<"checks: "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
