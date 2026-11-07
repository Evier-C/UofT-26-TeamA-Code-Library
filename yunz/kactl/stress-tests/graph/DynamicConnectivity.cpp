#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/DynamicConnectivity.h"

mt19937 rng(5);
int R(int a,int b){return rng()%(b-a+1)+a;}

int bf[N];
int bfind(int x){return bf[x]==x?x:bf[x]=bfind(bf[x]);}

int main(){
	long long checks=0;
	for(int it=0;it<3000;it++){
		bool big=it>=2990;
		int n=big?R(1000,100000):R(1,8),tm=big?100000:R(1,30);
		init(n,tm);
		// operations: at each time, toggle an edge (add if absent, remove if present)
		map<pair<int,int>,int> st;
		vector<set<pair<int,int>>> cur(tm+1);
		set<pair<int,int>> now;
		for(int t=1;t<=tm;t++){
			int u=R(1,n),v=R(1,n);if(u>v)swap(u,v);
			if(R(0,2)==0&&!now.empty()&&!big){
				auto x=*now.begin();u=x.first,v=x.second;
			}
			if(now.count({u,v})){
				now.erase({u,v});
				add(1,1,tm,st[{u,v}],t-1,u,v);st.erase({u,v});
			}else{
				now.insert({u,v});st[{u,v}]=t;
			}
			if(!big)cur[t]=now;
		}
		for(auto[ed,a]:st)add(1,1,tm,a,tm,ed.first,ed.second);
		solve(1,1,tm);
		assert(tp==0&&cc==n);
		if(big){
			// check last time only
			for(int i=1;i<=n;i++)bf[i]=i;
			int c=n;for(auto[u,v]:now)if(bfind(u)!=bfind(v))bf[bfind(u)]=bfind(v),c--;
			assert(ans[tm]==c);checks++;
			continue;
		}
		for(int t=1;t<=tm;t++){
			for(int i=1;i<=n;i++)bf[i]=i;
			int c=n;
			for(auto[u,v]:cur[t])if(bfind(u)!=bfind(v))bf[bfind(u)]=bfind(v),c--;
			assert(ans[t]==c);checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
