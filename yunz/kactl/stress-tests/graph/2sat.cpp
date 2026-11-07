#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/2sat.h"

mt19937 rng(23);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	long long checks=0;
	for(int it=0;it<30000;it++){
		int nn=R(1,8),m=R(0,20);
		init(nn);
		vector<array<int,4>> C;
		for(int i=0;i<m;i++){
			int x=R(1,nn),a=R(0,1),y=R(1,nn),b=R(0,1);
			if(R(0,9)==0)y=x,b=a;
			C.push_back({x,a,y,b});add(x,a,y,b);
		}
		bool ok=solve();
		bool exp=false;
		for(int mask=0;mask<(1<<nn)&&!exp;mask++){
			bool good=true;
			for(auto[x,a,y,b]:C)if((mask>>(x-1)&1)!=a&&(mask>>(y-1)&1)!=b)good=false;
			if(good)exp=true;
		}
		assert(ok==exp);
		if(ok)for(auto[x,a,y,b]:C)assert(ans[x]==a||ans[y]==b);
		checks++;
	}
	// large planted instance
	for(int rep=0;rep<20;rep++){
		int nn=2000;init(nn);
		vector<int> v(nn+1);for(int i=1;i<=nn;i++)v[i]=R(0,1);
		vector<array<int,4>> C;
		for(int i=0;i<6000;i++){
			int x=R(1,nn),y=R(1,nn),a=R(0,1),b=R(0,1);
			if(v[x]!=a&&v[y]!=b)a=v[x];
			C.push_back({x,a,y,b});add(x,a,y,b);
		}
		assert(solve());
		for(auto[x,a,y,b]:C)assert(ans[x]==a||ans[y]==b);
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
