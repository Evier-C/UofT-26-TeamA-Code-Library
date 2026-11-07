/**
 * Description: 最长严格上升子序列 ($n < N$). 最长不降: lower\_bound 改成 upper\_bound. a 为 ll 时 a 和 d 都改成 ll.
 * Usage: // 读入 n 和 a[1..n]
 * vector<int> id = lis(n); // 一个最长子序列的下标, 递增
 * int len = id.size(); // LIS 的长度
 * for(int i : id) cout << a[i] << ' '; // 输出子序列
 * // 多组数据不用清空
 * Time: O(n \log n)
 */
#pragma once

const int N=2e5+5;
int a[N],d[N],pos[N],pre[N];
vector<int>lis(int n){
	int len=0;
	for(int i=1;i<=n;i++){
		int k=lower_bound(d+1,d+len+1,a[i])-d;
		d[k]=a[i];
		pos[k]=i;
		pre[i]=pos[k-1];
		len=max(len,k);
	}
	vector<int>res;
	for(int i=pos[len];i;i=pre[i])res.push_back(i);
	reverse(res.begin(),res.end());
	return res;
}
