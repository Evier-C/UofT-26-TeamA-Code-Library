#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/CartesianTree.h"

mt19937 rng(11);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int bl[N],br[N],bL[N],bR[N],par[N],dep[N];
// brute: root of [l, r] is the leftmost minimum
int brute(int l,int r){
	if(l>r)return 0;
	int p=l;
	for(int i=l;i<=r;i++)if(a[i]<a[p])p=i;
	bL[p]=l;
	bR[p]=r;
	bl[p]=brute(l,p-1);
	br[p]=brute(p+1,r);
	return p;
}
void inorder(int p,vector<int>&o){
	if(!p)return;
	inorder(ls[p],o);
	o.push_back(p);
	inorder(rs[p],o);
}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		n=rnd(1,it%2?40:8);
		int V=rnd(1,10);
		for(int i=1;i<=n;i++)a[i]=rnd(-V,V);
		build(); // reused across tests
		int r=brute(1,n);
		assert(root==r);
		for(int i=1;i<=n;i++){
			assert(ls[i]==bl[i]&&rs[i]==br[i]);
			assert(L[i]==bL[i]&&R[i]==bR[i]);
		}
		vector<int>o;
		inorder(root,o);
		for(int i=0;i<n;i++)assert(o[i]==i+1);
		// LCA equals leftmost min position
		par[root]=0;
		dep[root]=0;
		vector<int>st={root};
		while(!st.empty()){
			int p=st.back();
			st.pop_back();
			for(int c:{ls[p],rs[p]})if(c){
				par[c]=p;
				dep[c]=dep[p]+1;
				st.push_back(c);
			}
		}
		for(int q=0;q<20;q++){
			int l=rnd(1,n),rr=rnd(l,n);
			int x=l,y=rr;
			while(x!=y){
				if(dep[x]<dep[y])swap(x,y);
				x=par[x];
			}
			int p=l;
			for(int i=l;i<=rr;i++)if(a[i]<a[p])p=i;
			assert(x==p);
			checks++;
		}
		// subarray-min counting covers each subarray exactly once
		ll s=0,e=0,cnt=0;
		for(int i=1;i<=n;i++){
			s+=a[i]*(i-L[i]+1)*(R[i]-i+1);
			cnt+=(ll)(i-L[i]+1)*(R[i]-i+1);
		}
		for(int l=1;l<=n;l++){
			ll mn=LLONG_MAX;
			for(int rr=l;rr<=n;rr++){
				mn=min(mn,a[rr]);
				e+=mn;
			}
		}
		assert(s==e&&cnt==(ll)n*(n+1)/2);
		checks++;
	}
	// large: sorted (deep chain), random; check intervals vs stack-free brute
	for(int t=0;t<3;t++){
		n=200000;
		for(int i=1;i<=n;i++)a[i]=t==0?i:t==1?n-i:rnd(0,1000000000);
		build();
		vector<int>o;
		// iterative inorder to avoid deep recursion
		vector<int>st;
		int p=root;
		while(p||!st.empty()){
			while(p){
				st.push_back(p);
				p=ls[p];
			}
			p=st.back();
			st.pop_back();
			o.push_back(p);
			p=rs[p];
		}
		for(int i=0;i<n;i++)assert(o[i]==i+1);
		for(int q=0;q<1000;q++){
			int i=rnd(1,n);
			int l=i,r=i;
			while(l>1&&a[l-1]>a[i])l--;
			while(r<n&&a[r+1]>=a[i])r++;
			if(t!=2&&q>20)break;
			assert(L[i]==l&&R[i]==r);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
