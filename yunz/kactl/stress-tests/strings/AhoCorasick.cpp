#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/AhoCorasick.h"

mt19937 rng(8);
char p[105][15],t[N];
int plen[105];
ll checks=0;
void test(int k,int maxl,int m,int al){
	init();
	for(int i=1;i<=k;i++){
		plen[i]=1+rng()%maxl;
		for(int j=1;j<=plen[i];j++)p[i][j]='a'+rng()%al;
		insert(p[i],plen[i],i);
	}
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	build();query(t,m);
	for(int i=1;i<=k;i++){
		int c=0;
		for(int j=1;j+plen[i]-1<=m;j++)
			if(!memcmp(t+j,p[i]+1,plen[i]))c++;
		assert(cnt[pos[i]]==c);checks++;
	}
	// 同一自动机换文本
	for(int i=0;i<=tot;i++)cnt[i]=0;
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	query(t,m);
	for(int i=1;i<=k;i++){
		int c=0;
		for(int j=1;j+plen[i]-1<=m;j++)
			if(!memcmp(t+j,p[i]+1,plen[i]))c++;
		assert(cnt[pos[i]]==c);checks++;
	}
}
int main(){
	for(int it=0;it<50000;it++)
		test(1+rng()%8,1+rng()%5,rng()%30,1+rng()%3);
	for(int it=0;it<200;it++)
		test(1+rng()%100,1+rng()%14,rng()%3000,1+rng()%26);
	init();
	int m=1000000;
	for(int i=1;i<=m;i++)t[i]='a';
	for(int i=1;i<=10;i++){
		for(int j=1;j<=i;j++)p[i][j]='a';
		insert(p[i],i,i);
	}
	build();query(t,m);
	for(int i=1;i<=10;i++)assert(cnt[pos[i]]==m-i+1);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
