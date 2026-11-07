#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/various/IntervalContainer.h"

const int V=60;
bool on[V+5];
void check(ll&checks){
	vector<pair<int,int>>want;
	ll cntOn=0;
	for(int i=0;i<=V;i++)if(on[i]){
		cntOn++;
		if(i&&on[i-1])want.back().second=i;
		else want.push_back({i,i});
	}
	assert((vector<pair<int,int>>(st.begin(),st.end())==want));
	assert(tot==cntOn);
	for(int x=-2;x<=V+2;x++){
		auto it=getIt(x);
		bool in=x>=0&&x<=V&&on[x];
		if(!in)assert(it==st.end());
		else assert(it!=st.end()&&it->first<=x&&x<=it->second);
	}
	checks++;
}
int main(){
	mt19937_64 rng(13);
	ll checks=0;
	add(1,5),add(7,9),add(6,6);
	assert(st.size()==1&&*st.begin()==make_pair(1,9));
	del(3,4);
	assert(st.size()==2&&tot==7);
	for(int t=0;t<3000;t++){
		st.clear(),tot=0; // 多组数据
		memset(on,0,sizeof on);
		for(int op=0;op<100;op++){
			int l=rng()%(V+1),r=rng()%(V+1);
			if(l>r)swap(l,r);
			if(rng()%2){add(l,r);for(int i=l;i<=r;i++)on[i]=1;}
			else{del(l,r);for(int i=l;i<=r;i++)on[i]=0;}
			check(checks);
		}
	}
	// 大范围随机
	st.clear(),tot=0;
	for(int i=0;i<200000;i++){
		int l=rng()%1000000000,r=l+rng()%1000;
		if(rng()%3)add(l,r);else del(l,r);
	}
	ll s=0;int last=INT_MIN;
	for(auto [l,r]:st)assert(l<=r&&l>last+1),s+=r-l+1,last=r;
	assert(s==tot);
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
