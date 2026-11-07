/**
 * Description: 带权二分图最优匹配 (KM / 匈牙利算法, $O(n^2 m)$ 版).
 * 问题: 左部 $n$ 个点, 右部 $m$ 个点, 要求 $n \le m$ (否则把矩阵转置),
 * 给每个左部点匹配一个不同的右部点, 使代价和最小.
 * 全部状态都在结构体 KM 里, 已定义全局对象 K; a 有 $N^2$ 个 ll,
 * 对象必须是全局 (或 static) 的. 第二个实例: 全局写 KM K2;
 * 输入: K.n, K.m 和代价矩阵 K.a[i][j] (左 $i$ 配右 $j$ 的代价, ll,
 * $1 \le i \le n$, $1 \le j \le m$). 没有的边设为很大的代价
 * (如 $10^{12}$, 要远小于 INF 除以 $n$), 答案达到这个量级说明
 * 不存在完美匹配.
 * 函数: K.km() 返回最小代价和; K.ans[i] 为左 $i$ 匹配的右部点,
 * K.p[j] 为右 $j$ 匹配的左部点 (0 表示未匹配).
 * 变形: 最大权完美匹配: a 取负, 答案再取负.
 * 最大权匹配 (可以不匹配): a[i][j] 取 $-\max(w,0)$, 并补 0 使 $n = m$,
 * 答案取负; 输出时跳过原图中不存在或权不为正的配对.
 * 注意: N 为 n, m 上限, 按题目修改. 多组数据直接覆盖 a, n, m.
 * Usage: cin>>K.n>>K.m; // 要求 n 不超过 m
 * for(int i=1;i<=K.n;i++)
 *   for(int j=1;j<=K.m;j++) cin>>K.a[i][j];
 * ll c=K.km(); // 最小代价和
 * for(int i=1;i<=K.n;i++) // 输出匹配
 *   cout<<i<<' '<<K.ans[i]<<endl;
 * // 最大权完美匹配: 读入 w 后 K.a[i][j]=-w; 答案为 -K.km()
 * Time: O(n^2 m)
 */
#pragma once

struct KM{
	static const int N=505; // n, m 的最大值
	static constexpr ll INF=1e18; // 大于任意可能的代价和
	int n,m,p[N],way[N],ans[N]; // p[j]: 右 j 匹配的左部点
	ll a[N][N],u[N],v[N],minv[N]; // u, v 为顶标
	bool used[N];
	ll km(){
		for(int i=0;i<=n;i++)u[i]=0;
		for(int j=0;j<=m;j++){
			v[j]=0;
			p[j]=0;
		}
		for(int i=1;i<=n;i++){
			p[0]=i; // 虚拟右部点 0 先配给 i
			int j0=0;
			for(int j=0;j<=m;j++){
				minv[j]=INF;
				used[j]=0;
			}
			do{ // 找一条到未匹配右部点的最短增广路
				used[j0]=1;
				int i0=p[j0],j1=0;
				ll delta=INF;
				for(int j=1;j<=m;j++){
					if(used[j])continue;
					ll cur=a[i0][j]-u[i0]-v[j];
					if(cur<minv[j]){
						minv[j]=cur;
						way[j]=j0;
					}
					if(minv[j]<delta){
						delta=minv[j];
						j1=j;
					}
				}
				for(int j=0;j<=m;j++){ // 修改顶标
					if(used[j]){
						u[p[j]]+=delta;
						v[j]-=delta;
					}else{
						minv[j]-=delta;
					}
				}
				j0=j1;
			}while(p[j0]);
			do{ // 沿增广路翻转
				int j1=way[j0];
				p[j0]=p[j1];
				j0=j1;
			}while(j0);
		}
		for(int j=1;j<=m;j++){
			if(p[j])ans[p[j]]=j;
		}
		return -v[0];
	}
}K;
