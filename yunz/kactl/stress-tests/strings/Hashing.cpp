#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/strings/Hashing.h"

mt19937 rng(7);
char s[Hash::N],t[Hash::N];
Hash H2; // 第二个实例
ll checks=0;
void test(int n,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	s[n+1]=0;
	H.build(s,n);
	for(int it=0;it<50;it++){
		int l1=1+rng()%n,l2=1+rng()%n;
		int L=1+rng()%(n-max(l1,l2)+1);
		bool eq=!memcmp(s+l1,s+l2,L);
		assert(eq==(H.get(l1,l1+L-1)==H.get(l2,l2+L-1)));
		for(int i=1;i<=L;i++)t[i]=s[l1+i-1];
		assert(H.calc(t,L)==H.get(l1,l1+L-1));
		checks+=2;
	}
	// 所有子串: 哈希相同当且仅当串相同
	if(n<=12){
		map<ll,string> mp;
		for(int l=1;l<=n;l++)for(int r=l;r<=n;r++){
			string x(s+l,s+r+1);
			ll h=H.get(l,r);
			if(mp.count(h))assert(mp[h]==x);
			else mp[h]=x;
			checks++;
		}
	}
}
void test2(int n,int m,int al){
	for(int i=1;i<=n;i++)s[i]='a'+rng()%al;
	for(int i=1;i<=m;i++)t[i]='a'+rng()%al;
	H.build(s,n);
	H2.build(t,m);
	for(int it=0;it<30;it++){
		int l1=1+rng()%n,l2=1+rng()%m;
		int L=1+rng()%min(n-l1+1,m-l2+1);
		bool eq=!memcmp(s+l1,t+l2,L);
		assert(eq==(H.get(l1,l1+L-1)==H2.get(l2,l2+L-1)));
		checks++;
	}
}
int main(){
	for(int it=0;it<50000;it++)test2(1+rng()%10,1+rng()%10,1+rng()%2);
	for(int it=0;it<100000;it++)test(1+rng()%12,1+rng()%3);
	for(int it=0;it<100;it++)test(1+rng()%100000,1+rng()%2);
	cout<<checks<<" checks"<<endl;
	cout<<"Tests passed!"<<endl;
}
