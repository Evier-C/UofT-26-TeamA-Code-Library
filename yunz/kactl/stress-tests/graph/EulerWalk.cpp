#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/EulerWalk.h"

mt19937 rng(29);
int R(int a,int b){return rng()%(b-a+1)+a;}

int main(){
	long long checks=0;
	for(int it=0;it<100000;it++){
		bool big=it>=99990;
		int nn=big?R(1,1000):R(1,6),mm=big?R(0,3000):R(0,10),d=R(0,1);
		EU.init(nn,d);
		vector<pair<int,int>> E;
		// sometimes make an EU.euler-friendly graph via a random walk
		if(R(0,1)){
			int u=R(1,nn);
			for(int i=0;i<mm;i++){int v=R(1,nn);E.push_back({u,v});u=v;}
			shuffle(E.begin(),E.end(),rng);
			if(!d)for(auto&[a,b]:E)if(R(0,1))swap(a,b);
		}else for(int i=0;i<mm;i++)E.push_back({R(1,nn),R(1,nn)});
		for(auto[a,b]:E)EU.addE(a,b);
		bool ok=EU.euler();
		// brute existence
		vector<int> in(nn+1),out(nn+1),dg(nn+1),f(nn+1);
		iota(f.begin(),f.end(),0);
		function<int(int)> fd=[&](int x){return f[x]==x?x:f[x]=fd(f[x]);};
		for(auto[a,b]:E)out[a]++,in[b]++,dg[a]++,dg[b]++,f[fd(a)]=fd(b);
		bool exp=true;
		set<int> roots;
		for(auto[a,b]:E)roots.insert(fd(a));
		if(roots.size()>1)exp=false;
		if(d){
			int p=0,q=0;
			for(int i=1;i<=nn;i++){
				int x=out[i]-in[i];
				if(x==1)p++;else if(x==-1)q++;else if(x!=0)exp=false;
			}
			if(p>1||q>1)exp=false;
		}else{
			int c=0;for(int i=1;i<=nn;i++)c+=dg[i]%2;
			if(c>2)exp=false;
		}
		assert(ok==exp);
		if(ok){
			int mE=E.size();
			assert(EU.len==mE+1&&EU.le==mE);
			vector<int> used(mE+1);
			for(int i=1;i<=mE;i++){
				int id=EU.ep[i];assert(id>=1&&id<=mE&&!used[id]);used[id]=1;
				auto[a,b]=E[id-1];int x=EU.path[i],y=EU.path[i+1];
				if(d)assert(a==x&&b==y);
				else assert((a==x&&b==y)||(a==y&&b==x));
			}
		}
		checks++;
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
