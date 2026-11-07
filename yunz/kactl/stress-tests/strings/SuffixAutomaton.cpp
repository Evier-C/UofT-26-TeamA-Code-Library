#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/SuffixAutomaton.h"

mt19937 rng(6);
char s[SAM::N];
SAM sam2; // 第二个实例
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	sam.init();
	for(int i=1;i<=n;i++)sam.extend(s[i]-'a');
	assert(sam.tot<=max(2,2*n-1)); // 状态数含根
	ll d=sam.calc();
	map<string,int> occ;
	string str(s+1,s+n+1);
	for(int i=0;i<n;i++)for(int l=1;i+l<=n;l++)occ[str.substr(i,l)]++;
	assert(d==(ll)occ.size());checks++;
	for(auto&[t,c]:occ){
		int u=1;
		for(char x:t)u=sam.ch[u][x-'a'];
		assert(u&&sam.siz[u]==c);checks++;
	}
	// 不出现的串
	for(int it=0;it<5;it++){
		string t;int m=1+rng()%5;
		for(int i=0;i<m;i++)t+='a'+rng()%(al+1);
		int u=1;
		for(char x:t)if(u)u=sam.ch[u][x-'a'];
		assert((u?sam.siz[u]:0)==(occ.count(t)?occ[t]:0));checks++;
	}
}
int main(){
	for(int it=0;it<100000;it++){
		int n=it%3==0?1+rng()%25:1+rng()%8;
		test(n,1+rng()%3);
	}
	for(int it=0;it<10;it++)test(100+rng()%100,1+rng()%2);
	// 两个实例交替使用, 互不影响
	for(int it=0;it<2000;it++){
		string a,b;
		int na=1+rng()%12,nb=1+rng()%12;
		for(int i=0;i<na;i++)a+='a'+rng()%2;
		for(int i=0;i<nb;i++)b+='a'+rng()%3;
		sam.init();
		sam2.init();
		for(int i=0;i<max(na,nb);i++){
			if(i<na)sam.extend(a[i]-'a');
			if(i<nb)sam2.extend(b[i]-'a');
		}
		set<string> da,db;
		for(int i=0;i<na;i++)for(int l=1;i+l<=na;l++)da.insert(a.substr(i,l));
		for(int i=0;i<nb;i++)for(int l=1;i+l<=nb;l++)db.insert(b.substr(i,l));
		assert(sam.calc()==(ll)da.size());
		assert(sam2.calc()==(ll)db.size());
		checks+=2;
	}
	sam.init();
	int n=500000;
	for(int i=1;i<=n;i++)sam.extend(rng()%26);
	sam.calc();
	sam.init();
	for(int i=1;i<=n;i++)sam.extend(0);
	assert(sam.calc()==n);
	assert(sam.siz[sam.ch[1][0]]==n);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
