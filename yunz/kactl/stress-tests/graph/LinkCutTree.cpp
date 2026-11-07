#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/LinkCutTree.h"

mt19937 rng(43);
int R(int a,int b){return rng()%(b-a+1)+a;}

int n;
const int N=3e5+5;
set<int> adj[N];
ll bv[N];
// path from x to y in forest, empty if not connected
vector<int> path(int x,int y){
	vector<int> pr(n+1,-1);pr[x]=0;queue<int> q;q.push(x);
	while(!q.empty()){int u=q.front();q.pop();for(int v:adj[u])if(pr[v]<0)pr[v]=u,q.push(v);}
	if(pr[y]<0)return {};
	vector<int> p;for(int z=y;z;z=pr[z])p.push_back(z);return p;
}

int main(){
	long long checks=0;
	for(int it=0;it<2000;it++){
		bool big=it>=1995;
		n=big?300:R(1,12);
		for(int i=1;i<=n;i++)adj[i].clear(),bv[i]=L.val[i]=R(-1000,1000);
		L.init(n);
		int Q=big?20000:300;
		for(int q=0;q<Q;q++){
			int op=R(0,4),x=R(1,n),y=R(1,n);
			vector<int> p=path(x,y);
			if(op==0){ // L.link
				L.link(x,y);
				if(p.empty())adj[x].insert(y),adj[y].insert(x);
			}else if(op==1){ // L.cut a random existing edge or random pair
				if(R(0,1)&&!adj[x].empty())y=*adj[x].begin();
				L.cut(x,y);
				if(adj[x].count(y))adj[x].erase(y),adj[y].erase(x);
			}else if(op==2){
				assert(L.connected(x,y)==!p.empty());
			}else if(op==3){
				ll v=R(-1000,1000);L.modify(x,v);bv[x]=v;
			}else{
				if(!p.empty()){
					L.split(x,y);ll s=0;for(int z:p)s+=bv[z];
					assert(L.sum[y]==s);
				}
			}
			checks++;
		}
	}
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
