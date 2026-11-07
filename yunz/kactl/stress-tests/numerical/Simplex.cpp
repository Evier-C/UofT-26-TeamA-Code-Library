#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../../content/numerical/Simplex.h"

mt19937 rng(7);
int M,Nv;
vector<vector<double>> AA;
vector<double> bb,cc;
// 解 k x k 方程组, 失败返回 false
bool solveSq(vector<vector<double>> a,vector<double>&x){
	int k=a.size();
	for(int i=0;i<k;i++){
		int p=i;
		for(int j=i;j<k;j++)if(fabs(a[j][i])>fabs(a[p][i]))p=j;
		if(fabs(a[p][i])<1e-9)return false;
		swap(a[i],a[p]);
		for(int j=0;j<k;j++)if(j!=i){
			double t=a[j][i]/a[i][i];
			for(int l=i;l<=k;l++)a[j][l]-=t*a[i][l];
		}
	}
	x.assign(k,0);
	for(int i=0;i<k;i++)x[i]=a[i][k]/a[i][i];
	return true;
}
// 枚举顶点 (可选再加盒子 x_j 不超过 B), 返回最优值, 无可行顶点返回 nan
double brute(double B){
	// 超平面: 约束 i, x_j=0, x_j=B
	vector<vector<double>> H;
	for(int i=0;i<M;i++){
		vector<double> h=AA[i];h.push_back(bb[i]);H.push_back(h);
	}
	for(int j=0;j<Nv;j++){
		vector<double> h(Nv+1,0);h[j]=1;H.push_back(h);
		h[Nv]=B;H.push_back(h);
	}
	int K=H.size();
	double best=NAN;
	vector<int> idx(Nv);
	// 枚举 Nv 个超平面的组合
	function<void(int,int)> rec=[&](int st,int d){
		if(d==Nv){
			vector<vector<double>> a;
			for(int t:idx)a.push_back(H[t]);
			vector<double> x;
			if(!solveSq(a,x))return;
			for(int j=0;j<Nv;j++)if(x[j]<-1e-7||x[j]>B+1e-7)return;
			for(int i=0;i<M;i++){
				double s=0;
				for(int j=0;j<Nv;j++)s+=AA[i][j]*x[j];
				if(s>bb[i]+1e-7)return;
			}
			double v=0;
			for(int j=0;j<Nv;j++)v+=cc[j]*x[j];
			if(std::isnan(best)||v>best)best=v;
			return;
		}
		for(int t=st;t<K;t++){idx[d]=t;rec(t+1,d+1);}
	};
	rec(0,0);
	return best;
}
double runLP(){ // 把 AA, bb, cc 填入模板数组并求解
	for(int i=1;i<=M;i++){
		for(int j=1;j<=Nv;j++)A[i][j]=AA[i-1][j-1];
		b[i]=bb[i-1];
	}
	for(int j=1;j<=Nv;j++)c[j]=cc[j-1];
	return simplex(M,Nv);
}
void checkX(double v){
	for(int j=1;j<=Nv;j++)assert(x[j]>-1e-6);
	for(int i=0;i<M;i++){
		double s=0;
		for(int j=0;j<Nv;j++)s+=AA[i][j]*x[j+1];
		assert(s<=bb[i]+1e-6);
	}
	double s=0;
	for(int j=0;j<Nv;j++)s+=cc[j]*x[j+1];
	assert(fabs(s-v)<1e-6*max(1.0,fabs(v)));
}
int main(){
	long long checks=0;
	// Usage 示例
	M=3;Nv=2;
	AA={{1,-1},{-1,1},{-1,-2}};bb={1,1,-4};cc={-1,-1};
	{
		double v=runLP();
		assert(fabs(v+7.0/3)<1e-9);
		checkX(v);
		checks++;
	}
	int cnt[3]={0,0,0};
	for(int it=0;it<20000;it++){
		Nv=rng()%3+1;M=rng()%4+1;
		int R=rng()%2?2:5;
		AA.assign(M,vector<double>(Nv));
		bb.assign(M,0);cc.assign(Nv,0);
		for(auto&row:AA)for(auto&v:row)v=(int)(rng()%(2*R+1))-R;
		for(auto&v:bb)v=(int)(rng()%(2*R+1))-R+(rng()%2?R:0);
		for(auto&v:cc)v=(int)(rng()%(2*R+1))-R;
		double v=runLP();
		double b1=brute(1e4),b2=brute(1e5);
		if(std::isnan(b1)){ // 无解
			assert(v==-INF);
			cnt[0]++;
		}else if(fabs(b2-b1)>1e-3){ // 无界
			assert(v==INF);
			cnt[1]++;
		}else{
			assert(fabs(v-b1)<1e-6*max(1.0,fabs(v)));
			checkX(v);
			// 格点暴力: 所有可行整点的目标值不超过 v
			int K=6;
			vector<int> p(Nv,0);
			while(1){
				bool ok=true;
				for(int i=0;i<M&&ok;i++){
					double s=0;
					for(int j=0;j<Nv;j++)s+=AA[i][j]*p[j];
					if(s>bb[i])ok=false;
				}
				if(ok){
					double s=0;
					for(int j=0;j<Nv;j++)s+=cc[j]*p[j];
					assert(s<=v+1e-6);
				}
				int j=0;
				while(j<Nv&&p[j]==K)p[j++]=0;
				if(j==Nv)break;
				p[j]++;
			}
			cnt[2]++;
		}
		checks++;
	}
	assert(cnt[0]>100&&cnt[1]>100&&cnt[2]>100);
	// 大规模: 强对偶 (原问题与对偶问题最优值相等)
	for(int it=0;it<200;it++){
		M=rng()%30+1;Nv=rng()%30+1;
		AA.assign(M,vector<double>(Nv));
		bb.assign(M,0);cc.assign(Nv,0);
		for(auto&row:AA)for(auto&v:row)v=(int)(rng()%21)-5;
		for(auto&v:bb)v=(int)(rng()%21);
		for(auto&v:cc)v=(int)(rng()%21)-10;
		double v=runLP();
		if(v==INF){checks++;continue;}
		assert(v>-INF);
		checkX(v);
		// 对偶: min b.y, A^T y 不小于 c, y 非负
		auto A0=AA;auto b0=bb;auto c0=cc;
		int m0=M,n0=Nv;
		M=n0;Nv=m0;
		AA.assign(M,vector<double>(Nv));
		for(int i=0;i<M;i++)for(int j=0;j<Nv;j++)AA[i][j]=-A0[j][i];
		bb.assign(M,0);for(int i=0;i<M;i++)bb[i]=-c0[i];
		cc.assign(Nv,0);for(int j=0;j<Nv;j++)cc[j]=-b0[j];
		double w=runLP();
		assert(fabs(v+w)<1e-6*max(1.0,fabs(v)));
		checkX(w);
		checks++;
	}
	cout<<"Tests passed! ("<<checks<<" checks)"<<endl;
}
