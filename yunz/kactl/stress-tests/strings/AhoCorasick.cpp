#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/AhoCorasick.h"

mt19937 rng(8);
char p[105][15],t[AC::N];
AC ac2; // 第二个实例
int plen[105];
ll checks=0;
void test(int k,int maxl,int m,int al){
	ac.init();
	for(int i=1;i<=k;i++){
		plen[i]=1+rng()%maxl;
		for(int j=1;j<=plen[i];j++)p[i][j]='a'+rng()%al;
		ac.insert(p[i],plen[i],i);
	}
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	ac.build();ac.query(t,m);
	for(int i=1;i<=k;i++){
		int c=0;
		for(int j=1;j+plen[i]-1<=m;j++)
			if(!memcmp(t+j,p[i]+1,plen[i]))c++;
		assert(ac.cnt[ac.pos[i]]==c);checks++;
	}
	// 同一自动机换文本
	for(int i=0;i<=ac.tot;i++)ac.cnt[i]=0;
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	ac.query(t,m);
	for(int i=1;i<=k;i++){
		int c=0;
		for(int j=1;j+plen[i]-1<=m;j++)
			if(!memcmp(t+j,p[i]+1,plen[i]))c++;
		assert(ac.cnt[ac.pos[i]]==c);checks++;
	}
}
void test2(int al){
	// ac 与 ac2 各建一个自动机, 在同一文本上查询
	int k=1+rng()%6,m=rng()%25;
	ac.init();
	ac2.init();
	for(int i=1;i<=k;i++){
		plen[i]=1+rng()%4;
		for(int j=1;j<=plen[i];j++)p[i][j]='a'+rng()%al;
		if(i&1)ac.insert(p[i],plen[i],i);
		else ac2.insert(p[i],plen[i],i);
	}
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	ac.build();
	ac2.build();
	ac.query(t,m);
	ac2.query(t,m);
	for(int i=1;i<=k;i++){
		int c=0;
		for(int j=1;j+plen[i]-1<=m;j++)
			if(!memcmp(t+j,p[i]+1,plen[i]))c++;
		int got=(i&1)?ac.cnt[ac.pos[i]]:ac2.cnt[ac2.pos[i]];
		assert(got==c);checks++;
	}
}
int main(){
	for(int it=0;it<20000;it++)test2(1+rng()%3);
	for(int it=0;it<50000;it++)
		test(1+rng()%8,1+rng()%5,rng()%30,1+rng()%3);
	for(int it=0;it<200;it++)
		test(1+rng()%100,1+rng()%14,rng()%3000,1+rng()%26);
	ac.init();
	int m=1000000;
	for(int i=1;i<=m;i++)t[i]='a';
	for(int i=1;i<=10;i++){
		for(int j=1;j<=i;j++)p[i][j]='a';
		ac.insert(p[i],i,i);
	}
	ac.build();ac.query(t,m);
	for(int i=1;i<=10;i++)assert(ac.cnt[ac.pos[i]]==m-i+1);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
