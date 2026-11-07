/**
 * Description: 二分图最大匹配 Hopcroft-Karp.
 * 数组大, 对象必须是全局 (或 static) 的; 已定义 HK,
 * 可再定义 HopcroftKarp HK2; 左部 $1..n$, 右部 $1..m$ 各自编号.
 * N 为左右部点数上限; dfs 递归深度可达 $n$.
 * Usage: HK.init(n,m); // 每组数据先调用
 * for(int i=1;i<=k;i++){
 *   cin>>u>>v; // 左 u, 右 v
 *   HK.g[u].push_back(v);
 * }
 * cout<<HK.hk()<<endl; // 最大匹配数
 * for(int u=1;u<=n;u++) // 左 u 匹配右 HK.mL[u], 0 为未匹配
 *   if(HK.mL[u]) cout<<u<<' '<<HK.mL[u]<<endl;
 * // 右 v 匹配左 HK.mR[v], 0 为未匹配
 * Time: O(E \sqrt{V})
 */
#pragma once

struct HopcroftKarp{
	static const int N=100005; // 左右部点数的最大值
	int n,m,mL[N],mR[N],d[N];
	vector<int>g[N];
	void init(int _n,int _m){
		n=_n;
		m=_m;
		for(int i=1;i<=n;i++)g[i].clear();
	}
	bool dfs(int u){
		int t=d[u]+1;
		d[u]=0; // 本轮不再访问 u
		for(int v:g[u]){
			if(!mR[v]||(d[mR[v]]==t&&dfs(mR[v]))){
				mL[u]=v;
				mR[v]=u;
				return true;
			}
		}
		return false;
	}
	int hk(){
		for(int i=1;i<=n;i++)mL[i]=0;
		for(int i=1;i<=m;i++)mR[i]=0;
		int res=0;
		while(true){
			// d[u] 为左部点 u 的层数, 0 表示不可用
			queue<int>q;
			bool found=false;
			for(int i=1;i<=n;i++){
				d[i]=0;
				if(!mL[i]){
					d[i]=1;
					q.push(i);
				}
			}
			while(!q.empty()){
				int u=q.front();
				q.pop();
				for(int v:g[u]){
					int w=mR[v];
					if(!w){
						found=true;
					}else if(!d[w]){
						d[w]=d[u]+1;
						q.push(w);
					}
				}
			}
			if(!found)return res;
			for(int i=1;i<=n;i++){
				if(!mL[i]&&dfs(i))res++;
			}
		}
	}
}HK;
