#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/SuffixAutomaton.h"

mt19937 rng(6);
char s[N];
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	init();
	for(int i=1;i<=n;i++)extend(s[i]-'a');
	assert(tot<=max(2,2*n-1)); // 状态数含根
	ll d=calc();
	map<string,int> occ;
	string str(s+1,s+n+1);
	for(int i=0;i<n;i++)for(int l=1;i+l<=n;l++)occ[str.substr(i,l)]++;
	assert(d==(ll)occ.size());checks++;
	for(auto&[t,c]:occ){
		int u=1;
		for(char x:t)u=ch[u][x-'a'];
		assert(u&&siz[u]==c);checks++;
	}
	// 不出现的串
	for(int it=0;it<5;it++){
		string t;int m=1+rng()%5;
		for(int i=0;i<m;i++)t+='a'+rng()%(al+1);
		int u=1;
		for(char x:t)if(u)u=ch[u][x-'a'];
		assert((u?siz[u]:0)==(occ.count(t)?occ[t]:0));checks++;
	}
}
int main(){
	for(int it=0;it<100000;it++){
		int n=it%3==0?1+rng()%25:1+rng()%8;
		test(n,1+rng()%3);
	}
	for(int it=0;it<10;it++)test(100+rng()%100,1+rng()%2);
	init();
	int n=500000;
	for(int i=1;i<=n;i++)extend(rng()%26);
	calc();
	init();
	for(int i=1;i<=n;i++)extend(0);
	assert(calc()==n);
	assert(siz[ch[1][0]]==n);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
