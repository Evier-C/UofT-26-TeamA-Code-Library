#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/FenwickTree2d.h"

mt19937 rng(5);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int main(){
	long long checks=0;
	for(int it=0;it<1500;it++){
		bool big=it>=1495;
		n=big?rnd(500,1000):rnd(1,12);
		m=big?rnd(500,1000):rnd(1,12);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=0; // clear
		vector<vector<ll>>a(n+1,vector<ll>(m+1));
		for(int s=0;s<(big?3000:200);s++){
			if(rng()%2){
				int x=rnd(1,n),y=rnd(1,m);ll v=rnd(-1000000,1000000);
				add(x,y,v);a[x][y]+=v;
			}else{
				int x1=rnd(1,n),x2=rnd(x1,n),y1=rnd(1,m),y2=rnd(y1,m);
				if(big)x2=min(n,x1+rnd(0,20)),y2=min(m,y1+rnd(0,20));
				ll e=0;
				for(int i=x1;i<=x2;i++)for(int j=y1;j<=y2;j++)e+=a[i][j];
				assert(query(x1,y1,x2,y2)==e);checks++;
				if(!big&&rng()%4==0){
					e=0;
					for(int i=1;i<=x2;i++)for(int j=1;j<=y2;j++)e+=a[i][j];
					assert(ask(x2,y2)==e),checks++;
				}
			}
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
