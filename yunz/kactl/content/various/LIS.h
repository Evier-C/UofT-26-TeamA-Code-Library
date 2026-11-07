/**
 * Description: 最长严格上升子序列 (LIS), 并求出一个具体的最长子序列.
 * 输入全局数组 a[1..n] ($n < N$), lis(n) 返回一个最长严格上升子序列的下标 (从小到大), 长度就是 size().
 * d[k] 为长度为 $k$ 的上升子序列的最小结尾值, 单调递增, 对每个 a[i] 二分出它能接在哪个长度后面;
 * pos[k] 为 d[k] 对应的下标, pre[i] 为以 $i$ 结尾时前一个元素的下标, 最后从 pos[len] 倒着走回去.
 * 最长不降子序列: 把 lower\_bound 改成 upper\_bound. 最长下降: 把 a 取相反数.
 * 只要长度不要方案时删掉 pos 和 pre. a 是 ll 时把 a 和 d 都改成 ll.
 * 多组数据不需要清空.
 * Usage: // 读入 n 和 a[1..n]
 * vector<int> id = lis(n);
 * int len = id.size(); // LIS 的长度
 * for(int i : id) cout << a[i] << ' '; // 输出子序列
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
