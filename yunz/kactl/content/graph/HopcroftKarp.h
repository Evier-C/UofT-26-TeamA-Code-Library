/**
 * Description: 二分图最大匹配 Hopcroft-Karp. 左部点 $1..n$, 右部点 $1..m$,
 * g[u] 存左部点 $u$ 连向的右部点. 返回匹配数.
 * mL[u] 为左部点 $u$ 匹配的右部点, mR[v] 为右部点 $v$ 匹配的左部点,
 * 未匹配为 0. bfs 按层分组, dfs 只走下一层, 每轮找一批最短增广路.
 * Usage: init(n,m); // 多组数据每次调用
 * g[u].push_back(v); // 左 u 连右 v
 * int res=hk();
 * for(int u=1;u<=n;u++) if(mL[u]) cout<<u<<' '<<mL[u]<<endl;
 * Time: O(E \sqrt{V})
 */
#pragma once

const int N=1e5+5; // 左右部点数的最大值
int n,m,mL[N],mR[N],d[N];
vector<int>g[N];
void init(int _n,int _m){
	n=_n;m=_m;
	for(int i=1;i<=n;i++)g[i].clear();
}
bool dfs(int u){
	int t=d[u]+1;d[u]=0; // 本轮不再访问 u
	for(int v:g[u])
		if(!mR[v]||(d[mR[v]]==t&&dfs(mR[v]))){
			mL[u]=v;mR[v]=u;return true;
		}
	return false;
}
int hk(){
	for(int i=1;i<=n;i++)mL[i]=0;
	for(int i=1;i<=m;i++)mR[i]=0;
	int res=0;
	while(true){
		// d[u] 为左部点 u 的层数, 0 表示不可用
		queue<int>q;bool found=false;
		for(int i=1;i<=n;i++){
			d[i]=0;
			if(!mL[i])d[i]=1,q.push(i);
		}
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:g[u]){
				if(!mR[v])found=true;
				else if(!d[mR[v]])d[mR[v]]=d[u]+1,q.push(mR[v]);
			}
		}
		if(!found)return res;
		for(int i=1;i<=n;i++)if(!mL[i])res+=dfs(i);
	}
}
