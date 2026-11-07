/**
 * Description: 最长严格上升子序列, 返回一个最长的子序列的下标 (递增).
 * d[k] 为长度 k 的上升子序列的最小结尾, pos[k] 为它的下标, pre 记前驱.
 * 最长不降子序列: 把 lower\_bound 改成 upper\_bound.
 * Usage: // 读入 n 和 a[1..n]
 * vector<int> id = lis(n); // 值为 a[id[i]]
 * // 多组数据不用清空
 * Time: O(N \log N)
 */
#pragma once

const int N=2e5+5;
int a[N],d[N],pos[N],pre[N]; // a 的类型可以改成 ll, d 也要改
vector<int>lis(int n){
	int len=0;
	for(int i=1;i<=n;i++){
		int k=lower_bound(d+1,d+len+1,a[i])-d;
		d[k]=a[i],pos[k]=i,pre[i]=pos[k-1];
		len=max(len,k);
	}
	vector<int>res;
	for(int i=pos[len];i;i=pre[i])res.push_back(i);
	reverse(res.begin(),res.end());
	return res;
}
