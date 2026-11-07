// Checks every code block of the convolution guide (\paragraph{卷积用法}) in
// content/numerical/chapter.tex against brute force. Blocks are copied verbatim.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/FastFourierTransform.h"
#include "../../content/numerical/NumberTheoreticTransform.h"
#include "../../content/numerical/FWT.h"

vector<ll> R1c,R1d,R1t;
void block1(vector<ll> a,vector<ll> b){
// ---- guide block 1 (copied verbatim) ----
// a[i], b[i] 为 x^i 的系数
vector<ll> c=nttConv(a,b); // 模 998244353, 先取模
vector<ll> d=conv(a,b); // 精确整数 (FFT), 可有负数
// 差卷积 e[k]=sum a[i]*b[i+k], k 从 -(n-1) 到 m-1:
vector<ll> rb(b.rbegin(),b.rend()); // m=b.size()
vector<ll> t=conv(a,rb); // e[k] 即 t[m-1-k]
// ---- end of block ----
	R1c=c;R1d=d;R1t=t;
}
// ---- guide block 2 (copied verbatim) ----
string bigMul(string s,string t){ // 十进制, 无负号
	int n=s.size();
	int m=t.size();
	vector<ll> a(n),b(m); // 低位在前
	for(int i=0;i<n;i++)
		a[i]=s[n-1-i]-'0';
	for(int i=0;i<m;i++)
		b[i]=t[m-1-i]-'0';
	vector<ll> c=conv(a,b);
	string r;
	ll carry=0;
	for(int i=0;i<(int)c.size()||carry;i++){
		if(i<(int)c.size())
			carry+=c[i];
		r+=char('0'+carry%10);
		carry/=10;
	}
	while(r.size()>1&&r.back()=='0') // 去前导 0
		r.pop_back();
	reverse(r.begin(),r.end());
	return r;
}
// ---- end of block ----

// ---- guide block 3 (copied verbatim) ----
vector<ll> pairSum(vector<int>&v,int V){
	vector<ll> cnt(V+1);
	for(int x:v)
		cnt[x]++;
	vector<ll> f=conv(cnt,cnt); // 有序对, 含 i=j
	for(int x:v)
		f[2*x]--; // 去掉 i=j
	for(auto&y:f)
		y/=2; // 变成无序对 i<j
	return f; // f[k] 为对数, 长度 2V+1
}
// ---- end of block ----

// ---- guide block 4 (copied verbatim) ----
ll wv(char c){return c=='*'?0:c-'a'+1;} // 通配符为 0
vector<int> wildMatch(string s,string p){
	int n=s.size();
	int m=p.size();
	vector<int> res; // 匹配的起点, 下标从 0 开始
	if(m>n)
		return res;
	vector<ll> S[4],P[4]; // S[k][i] 为 s_i 的 k 次方
	for(int k=1;k<=3;k++){
		S[k].resize(n);
		P[k].resize(m);
	}
	for(int i=0;i<n;i++){
		ll v=wv(s[i]);
		S[1][i]=v;
		S[2][i]=v*v;
		S[3][i]=v*v*v;
	}
	for(int j=0;j<m;j++){ // P 为 p 反转
		ll v=wv(p[m-1-j]);
		P[1][j]=v;
		P[2][j]=v*v;
		P[3][j]=v*v*v;
	}
	vector<ll> c1=nttConv(P[3],S[1]);
	vector<ll> c2=nttConv(P[2],S[2]);
	vector<ll> c3=nttConv(P[1],S[3]);
	for(int i=0;i+m<=n;i++){
		int t=i+m-1;
		if((c1[t]-2*c2[t]+c3[t]+2*MOD)%MOD==0)
			res.push_back(i);
	}
	return res;
}
// ---- end of block ----

// ---- guide block 5 (copied verbatim) ----
vector<ll> pairXor(vector<int>&v,int K){
	vector<ll> cnt(1<<K);
	for(int x:v)
		cnt[x]++;
	vector<ll> f=xorConv(cnt,cnt); // 有序对, 含 i=j
	f[0]-=v.size(); // i=j 时 xor 为 0
	for(auto&y:f)
		y/=2;
	return f;
}
// ---- end of block ----

vector<ll> R5g,R5h;
void block5b(vector<ll> a){
// ---- guide block 5 (rest) (copied verbatim) ----
// or 同理: f=orConv(cnt,cnt), 对每个 x 做 f[x]--, 再除 2
// 子集和: g[S]=sum a[T], T 取遍 S 的子集
vector<ll> g=a;
fwtOr(g,1); // fwtOr(g,-1) 还原
// 超集和: fwtAnd(g,1)
// ---- end of block ----
	R5g=g;
	fwtOr(g,-1); // 还原
	R5h=g;
}

mt19937 rng(19);
string brMul(string s,string t){
	int n=s.size(),m=t.size();
	vector<int> c(n+m+1,0);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)c[i+j]+=(s[n-1-i]-'0')*(t[m-1-j]-'0');
	for(int i=0;i+1<(int)c.size();i++)c[i+1]+=c[i]/10,c[i]%=10;
	string r;
	for(int x:c)r+=char('0'+x);
	while(r.size()>1&&r.back()=='0')r.pop_back();
	reverse(r.begin(),r.end());
	return r;
}
int main(){
	long long checks=0;
	// block 1
	for(int it=0;it<5000;it++){
		int n=rng()%30+1,m=rng()%30+1;
		vector<ll> a(n),b(m);
		for(auto&x:a)x=rng()%1000;
		for(auto&x:b)x=rng()%1000;
		block1(a,b);
		vector<ll> w(n+m-1,0);
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)w[i+j]+=a[i]*b[j];
		assert(R1d==w);
		for(auto&x:w)x%=MOD;
		assert(R1c==w);
		for(int k=-(n-1);k<=m-1;k++){
			ll e=0;
			for(int i=0;i<n;i++)if(i+k>=0&&i+k<m)e+=a[i]*b[i+k];
			assert(R1t[m-1-k]==e);
		}
		checks+=3;
	}
	// block 2
	for(int it=0;it<5000;it++){
		auto gen=[&](){
			int len=rng()%40+1;
			string s;
			for(int i=0;i<len;i++)s+=char('0'+rng()%10);
			if(rng()%5==0)s=string(rng()%3+1,'0');
			else if(s[0]=='0'&&rng()%2)s[0]='1';
			return s;
		};
		string s=gen(),t=gen();
		assert(bigMul(s,t)==brMul(s,t));
		checks++;
	}
	{
		string s(3000,'9'),t(2500,'9');
		assert(bigMul(s,t)==brMul(s,t));
		for(auto&ch:s)ch='0'+rng()%10;
		s[0]='7';
		assert(bigMul(s,t)==brMul(s,t));
		checks+=2;
	}
	// block 3
	for(int it=0;it<5000;it++){
		int n=rng()%30+1,V=rng()%20;
		vector<int> v(n);
		for(auto&x:v)x=rng()%(V+1);
		vector<ll> f=pairSum(v,V),w(2*V+1,0);
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)w[v[i]+v[j]]++;
		assert(f==w);
		checks++;
	}
	// block 4
	for(int it=0;it<20000;it++){
		int n=rng()%30+1,m=rng()%8+1;
		int sig=rng()%3+1;
		string s,p;
		for(int i=0;i<n;i++)s+=rng()%5==0?'*':char('a'+rng()%sig);
		for(int i=0;i<m;i++)p+=rng()%4==0?'*':char('a'+rng()%sig);
		if(rng()%3==0)s[rng()%n]='z';
		vector<int> got=wildMatch(s,p),w;
		for(int i=0;i+m<=n;i++){
			bool ok=true;
			for(int j=0;j<m;j++)
				if(s[i+j]!='*'&&p[j]!='*'&&s[i+j]!=p[j])ok=false;
			if(ok)w.push_back(i);
		}
		assert(got==w);
		checks++;
	}
	{ // 较大
		int n=200000,m=1000;
		string s,p;
		for(int i=0;i<n;i++)s+=rng()%10==0?'*':char('a'+rng()%2);
		for(int i=0;i<m;i++)p+=rng()%2?'*':char('a'+rng()%2);
		vector<int> got=wildMatch(s,p),w;
		for(int i=0;i+m<=n;i++){
			bool ok=true;
			for(int j=0;j<m&&ok;j++)
				if(s[i+j]!='*'&&p[j]!='*'&&s[i+j]!=p[j])ok=false;
			if(ok)w.push_back(i);
		}
		assert(got==w);
		checks++;
	}
	// block 5
	for(int it=0;it<5000;it++){
		int K=rng()%6,n=rng()%30+1;
		vector<int> v(n);
		for(auto&x:v)x=rng()%(1<<K);
		vector<ll> f=pairXor(v,K),w(1<<K,0),wo(1<<K,0);
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)w[v[i]^v[j]]++,wo[v[i]|v[j]]++;
		assert(f==w);
		// 注释里的 or 写法
		vector<ll> cnt(1<<K);
		for(int x:v)cnt[x]++;
		vector<ll> fo=orConv(cnt,cnt);
		for(int x:v)fo[x]--;
		for(auto&y:fo)y/=2;
		assert(fo==wo);
		vector<ll> a(1<<K);
		for(auto&x:a)x=(ll)(rng()%201)-100;
		block5b(a);
		for(int S=0;S<(1<<K);S++){
			ll t=0;
			for(int T=0;T<(1<<K);T++)if((T&S)==T)t+=a[T];
			assert(R5g[S]==t);
		}
		assert(R5h==a);
		checks+=3;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
