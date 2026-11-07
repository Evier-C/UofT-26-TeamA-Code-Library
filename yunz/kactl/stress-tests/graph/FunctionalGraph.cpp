#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/graph/FunctionalGraph.h"

mt19937 rng(31);
int R(int a,int b){return rng()%(b-a+1)+a;}


// undirected pseudoforest test
long long testPseudo(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		bool big=it>=19995;
		int n=big?R(50000,100000):R(1,10);
		// split into components, each: random tree + one extra edge
		vector<int> lab(n+1);iota(lab.begin(),lab.end(),0);
		shuffle(lab.begin()+1,lab.end(),rng);
		vector<pair<int,int>> E;
		int i=1;
		while(i<=n){
			int s=min(n-i+1,big?R(1,30000):R(1,n));
			for(int j=1;j<s;j++){
				int p=R(0,j-1);E.push_back({lab[i+j],lab[i+p]});
			}
			int t=R(0,4);
			int u=lab[i+R(0,s-1)],v=lab[i+R(0,s-1)];
			if(t==0)v=u; // self loop
			else if(t==1&&s>1){auto e=E[E.size()-R(1,s-1)];u=e.first;v=e.second;} // parallel
			E.push_back({u,v});
			i+=s;
		}
		shuffle(E.begin(),E.end(),rng);
		for(auto&[u,v]:E)if(R(0,1))swap(u,v);
		int m=E.size();assert(m==n);
		PT.init(n);
		for(auto[u,v]:E)PT.addE(u,v);
		PT.solve(n);
		// brute: cycle edges = non-bridges
		vector<int> cycE(m+1),onc(n+1);
		vector<vector<pair<int,int>>> adj(n+1);
		for(int k=0;k<m;k++){auto[u,v]=E[k];adj[u].push_back({v,k+1});adj[v].push_back({u,k+1});}
		if(!big){
			for(int k=1;k<=m;k++){
				auto[u,v]=E[k-1];
				vector<int> vis(n+1);vector<int> st={u};vis[u]=1;
				while(!st.empty()){int x=st.back();st.pop_back();
					for(auto[y,id]:adj[x])if(id!=k&&!vis[y])vis[y]=1,st.push_back(y);}
				if(vis[v])cycE[k]=1,onc[u]=onc[v]=1;
			}
		}else{
			for(int k=1;k<=PT.cnt;k++)for(int id:PT.ce[k])cycE[id]=1;
			for(int k=1;k<=m;k++)if(cycE[k])onc[E[k-1].first]=onc[E[k-1].second]=1;
		}
		for(int x=1;x<=n;x++)assert(PT.on[x]==onc[x]);
		// cycles in order
		vector<int> seenE(m+1),seenV(n+1);
		int totE=0;
		for(int k=1;k<=PT.cnt;k++){
			auto&c=PT.cyc[k];auto&ce=PT.ce[k];
			int L=c.size();assert(L>0&&(int)ce.size()==L);
			for(int j=0;j<L;j++){
				int x=c[j],y=c[(j+1)%L],id=ce[j];
				assert(!seenV[x]);seenV[x]=1;
				assert(id>=1&&id<=m&&!seenE[id]&&cycE[id]);seenE[id]=1;totE++;
				auto[a,b]=E[id-1];
				assert((a==x&&b==y)||(a==y&&b==x));
				assert(PT.bel[x]==k&&PT.pos[x]==j&&PT.rt[x]==x&&PT.dep[x]==0&&PT.fa[x]==0);
			}
		}
		int nc=0;for(int k=1;k<=m;k++)nc+=cycE[k];
		assert(totE==nc);
		for(int x=1;x<=n;x++)assert(seenV[x]==onc[x]);
		// rt/dep by BFS from each cycle vertex through non-cycle vertices
		vector<int> brt(n+1),bd(n+1,-1);
		for(int c=1;c<=n;c++)if(onc[c]){
			brt[c]=c;bd[c]=0;queue<int> q;q.push(c);
			while(!q.empty()){int x=q.front();q.pop();
				for(auto[y,id]:adj[x])if(!onc[y]&&bd[y]<0)bd[y]=bd[x]+1,brt[y]=c,q.push(y);}
		}
		vector<int> inOrd(n+1);
		for(int k=1;k<=n;k++){int x=PT.ord[k];assert(!inOrd[x]);inOrd[x]=k;}
		for(int x=1;x<=n;x++){
			assert(PT.rt[x]==brt[x]&&PT.dep[x]==bd[x]);
			assert(PT.bel[x]==PT.bel[brt[x]]);
			if(!onc[x]){
				int f=PT.fa[x];
				assert(f&&PT.dep[f]==PT.dep[x]-1&&inOrd[f]<inOrd[x]);
			}
			checks++;
		}
	}
	return checks;
}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		bool big=it>=19995;
		int n=big?200000:R(1,10);
		for(int i=1;i<=n;i++)FG.a[i]=R(1,n);
		if(big&&it%2)for(int i=1;i<=n;i++)FG.a[i]=i<n?i+1:R(1,n);
		FG.solve(n);
		// on cycle: FG.a^k(x)==x for some k in [1,n]
		vector<int> on(n+1);
		if(!big){
			for(int x=1;x<=n;x++){int y=x;for(int k=0;k<n;k++){y=FG.a[y];if(y==x){on[x]=1;break;}}}
		}else{
			// mark via cycle arrays and verify ring structure below
			for(int k=1;k<=FG.cnt;k++)for(int x:FG.cyc[k])on[x]=1;
		}
		vector<int> seen(n+1);
		for(int k=1;k<=FG.cnt;k++){
			int L=FG.cyc[k].size();assert(L>0);
			for(int j=0;j<L;j++){
				int x=FG.cyc[k][j];assert(on[x]&&!seen[x]);seen[x]=1;
				assert(FG.a[x]==FG.cyc[k][(j+1)%L]);
				assert(FG.bel[x]==k&&FG.pos[x]==j&&FG.rt[x]==x&&FG.dep[x]==0);
			}
		}
		for(int x=1;x<=n;x++){
			assert(seen[x]==on[x]);
			if(!big){
				int y=x,d=0;while(!on[y])y=FG.a[y],d++;
				assert(FG.rt[x]==y&&FG.dep[x]==d&&FG.bel[x]==FG.bel[y]&&FG.pos[x]==FG.pos[y]);
				// k steps
				int L=FG.cyc[FG.bel[x]].size();
				int z=x;
				for(int k=0;k<3*n;k++){
					if(k>=FG.dep[x])assert(z==FG.cyc[FG.bel[x]][(FG.pos[x]+k-FG.dep[x])%L]);
					z=FG.a[z];
				}
			}else{
				if(!on[x])assert(FG.dep[x]==FG.dep[FG.a[x]]+1&&FG.rt[x]==FG.rt[FG.a[x]]);
			}
			checks++;
		}
	}
	checks+=testPseudo();
	cout<<"checks "<<checks<<endl;
	cout<<"Tests passed!"<<endl;
}
