/**
 * Description: 带权二分图最小代价匹配 (KM), 要求 $n \le m$ (否则转置).
 * a 有 $N^2$ 个 ll, 对象必须是全局 (或 static) 的; 已定义 K,
 * 可再定义 KM K2; 下标从 1 开始. 不存在的边代价设为 $10^{12}$ 左右
 * (要远小于 INF 除以 $n$), 答案达到该量级说明无完美匹配.
 * Usage: cin>>K.n>>K.m; // 多组数据直接覆盖 n, m, a
 * for(int i=1;i<=K.n;i++)
 *   for(int j=1;j<=K.m;j++) cin>>K.a[i][j];
 * ll c=K.km(); // 最小代价和
 * for(int i=1;i<=K.n;i++) // 左 i 匹配右 K.ans[i]
 *   cout<<i<<' '<<K.ans[i]<<endl;
 * // 右 j 匹配左 K.p[j], 0 为未匹配
 * // 最大权完美匹配: K.a[i][j]=-w; 答案为 -K.km()
 * // 最大权匹配, 可不匹配: K.a[i][j]=-max(w,0LL), 补 0 使
 * // n 等于 m, 答案 -K.km(), 输出时跳过不存在或权不为正的配对
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
