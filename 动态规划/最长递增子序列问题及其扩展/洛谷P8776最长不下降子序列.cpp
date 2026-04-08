/*
给定一个长度为 N 的整数序列：A_1, A_2,.., A_N。现在你有一次机会，
将其中连续的 K 个数修改成任意一个相同值。请你计算如何修改可以使修改后的数列的最长不下降子序列最长，请输出这个最长的长度。
最长不下降子序列是指序列中的一个子序列，子序列中的每个数不小于在它之前的数。

输入格式
输入第一行包含两个整数 N 和 K。
第二行包含 N 个整数 A_1, A_2,.., A_N。

输出格式
输出一行包含一个整数表示答案。
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
int n, k;
int bins(vector<int>& right,int tar)
{
	int l = 0, r = right.size() - 1;
	int ret = -1;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (right[mid] < tar)
		{
			ret = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	//我们一定要尝试所有的k长度的子数组作为待修改的位置，进行修改，找到一个最大值
	//思考：应该将这连续k个数字改为多少？从哪里开始改？
	//由于是最长不上升子序列，能将一段数字变为相同的值一定是不会使得答案更差的
	//发现：假设数组a中一个最长不下降子序列:a..b..c.....d
	//我们发现假设在c....d这一段修改，我们可以让被修改的一段紧贴d
	//也就是说改为形如c..ddddd
	//因为我们除了被修改的这一段，其余的该不选择还是不选择，因此答案不会更差
	//如何遍历？
	//我们考虑遍历每个点作为被修改的点，点i前面k个数字全变为a[i],
	//这样一来我们只需求[0...i-k]上最长不下降子序列(但是要求这个子序列结尾的数字<=a[i])
	//再加上[i...n]上以i为起点的最长不下降子序列
	//再加上被修改的k个数字，即可算出每个分割点i对应的值
	//不过注意：我们一定要尝试所有的k长度的子数组作为待修改的位置，
	//上面的情况要求要有一个结尾的数字，但是还有一种情况就是无结尾数字，就是最后k个数字
	//我们只需找到[0...n-k-1]上最长不下降子序列，再+k即可
	//还是：做划分，枚举分割点，处理前缀后缀的思想 
	

	//预处理后缀：suf[i]表示以i开头的最长不下降子序列长度
	//为了得出suf，逆向思考，倒序遍历，处理以每个位置结尾的最长不上升子序列，
	//反过来看就是每个位置开头的最长不下降子序列
	//为什么这样做：处理以每个位置结尾我们才有nlogn的贪心优化解
	vector<int> suf(n);
	//right数组相当于逆向的ends
	vector<int> right;
	for (int i = n - 1; i >= 0; i--)
	{
		//最长不上升子序列，right记录每个位置结尾的最大值
		//二分要找严格小于a[i]的第一个位置(严格小于a[i]的最靠左位置)
		//right是一个不递增序列
		int id = bins(right, a[i]);
		if (id == -1)
		{
			right.emplace_back(a[i]);
			suf[i] = right.size();
		}
		else {
			right[id] = a[i];
			suf[i] = id + 1;
		}
	}
	
	//枚举分割点，一边枚举，一边计算前面的结尾位置不超过a[i]位置的最长不下降子序列
	//具体而言，我们按照正常来维护ends数组，每次在ends数组中查找a[i]即可
	vector<int> ends;
	int ans = -INF;
	//pos表示作为分割点的位置
	for (int i = 0, pos = k; pos < n; i++,pos++)
	{
		//查找a[pos]位置，ends数组不递减，我们需要的查找是>a[pos]的第一个位置
		auto it2 = upper_bound(ends.begin(), ends.end(), a[pos]);
		int tmp;
		if (it2 == ends.end())
		{
			tmp = ends.size();
		}
		else tmp = it2 - ends.begin();
		ans = max(ans, tmp + k + suf[pos]);
		//将i加入ends
		auto it = upper_bound(ends.begin(), ends.end(), a[i]);
		if (it == ends.end())
		{
			ends.emplace_back(a[i]);
		}
		else {
			int id = it - ends.begin();
			ends[id] = a[i];
		}
	}
	//最后一种情况，修改最后k个元素
	ans = max(ans, k + (int)ends.size());
	cout << ans << '\n';
	return 0;
}