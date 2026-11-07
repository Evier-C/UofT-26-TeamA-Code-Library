#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/data-structures/CartesianTree.h"

mt19937 rng(11);
int rnd(int lo,int hi){return lo+(int)(rng()%(unsigned)(hi-lo+1));}

int bl[200005],br[200005],bL[200005],bR[200005],par[200005],dep[200005];
// brute: ct.root of [l, r] is the leftmost minimum
int brute(int l,int r){
	if(l>r)return 0;
	int p=l;
	for(int i=l;i<=r;i++)if(ct.a[i]<ct.a[p])p=i;
	bL[p]=l;
	bR[p]=r;
	bl[p]=brute(l,p-1);
	br[p]=brute(p+1,r);
	return p;
}
void inorder(int p,vector<int>&o){
	if(!p)return;
	inorder(ct.ls[p],o);
	o.push_back(p);
	inorder(ct.rs[p],o);
}

int main(){
	long long checks=0;
	for(int it=0;it<20000;it++){
		ct.n=rnd(1,it%2?40:8);
		int V=rnd(1,10);
		for(int i=1;i<=ct.n;i++)ct.a[i]=rnd(-V,V);
		ct.build(); // reused across tests
		int r=brute(1,ct.n);
		assert(ct.root==r);
		for(int i=1;i<=ct.n;i++){
			assert(ct.ls[i]==bl[i]&&ct.rs[i]==br[i]);
			assert(ct.L[i]==bL[i]&&ct.R[i]==bR[i]);
		}
		vector<int>o;
		inorder(ct.root,o);
		for(int i=0;i<ct.n;i++)assert(o[i]==i+1);
		// LCA equals leftmost min position
		par[ct.root]=0;
		dep[ct.root]=0;
		vector<int>st={ct.root};
		while(!st.empty()){
			int p=st.back();
			st.pop_back();
			for(int c:{ct.ls[p],ct.rs[p]})if(c){
				par[c]=p;
				dep[c]=dep[p]+1;
				st.push_back(c);
			}
		}
		for(int q=0;q<20;q++){
			int l=rnd(1,ct.n),rr=rnd(l,ct.n);
			int x=l,y=rr;
			while(x!=y){
				if(dep[x]<dep[y])swap(x,y);
				x=par[x];
			}
			int p=l;
			for(int i=l;i<=rr;i++)if(ct.a[i]<ct.a[p])p=i;
			assert(x==p);
			checks++;
		}
		// subarray-min counting covers each subarray exactly once
		ll s=0,e=0,cnt=0;
		for(int i=1;i<=ct.n;i++){
			s+=ct.a[i]*(i-ct.L[i]+1)*(ct.R[i]-i+1);
			cnt+=(ll)(i-ct.L[i]+1)*(ct.R[i]-i+1);
		}
		for(int l=1;l<=ct.n;l++){
			ll mn=LLONG_MAX;
			for(int rr=l;rr<=ct.n;rr++){
				mn=min(mn,ct.a[rr]);
				e+=mn;
			}
		}
		assert(s==e&&cnt==(ll)ct.n*(ct.n+1)/2);
		checks++;
	}
	// large: sorted (deep chain), random; check intervals vs stack-free brute
	for(int t=0;t<3;t++){
		ct.n=200000;
		for(int i=1;i<=ct.n;i++)ct.a[i]=t==0?i:t==1?ct.n-i:rnd(0,1000000000);
		ct.build();
		vector<int>o;
		// iterative inorder to avoid deep recursion
		vector<int>st;
		int p=ct.root;
		while(p||!st.empty()){
			while(p){
				st.push_back(p);
				p=ct.ls[p];
			}
			p=st.back();
			st.pop_back();
			o.push_back(p);
			p=ct.rs[p];
		}
		for(int i=0;i<ct.n;i++)assert(o[i]==i+1);
		for(int q=0;q<1000;q++){
			int i=rnd(1,ct.n);
			int l=i,r=i;
			while(l>1&&ct.a[l-1]>ct.a[i])l--;
			while(r<ct.n&&ct.a[r+1]>=ct.a[i])r++;
			if(t!=2&&q>20)break;
			assert(ct.L[i]==l&&ct.R[i]==r);
			checks++;
		}
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
