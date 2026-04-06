#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int n, k;
vector<ll> a;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	a.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	//dp[i]表示以i结尾的累加和不超过k的最长子数组的长度
	//来到每个位置，假设到当前位置前缀和为sum,要找不大于k的，
	//即需要sum-pre<=k
	//pre>=sum-k
	//我们不能来到每个i都向前面去遍历找尽量靠左的满足>=sum-k的位置
	//因为我们要找的pre是要>=某个数字，
	//举例说明,7,12,10,10,14
	//如果我们要找大于等于10的，实际上12就够了，因为>=12的必定>=10，而且12更靠左，更优
	//因此我们只需要记录一个单调的数组
	//将我们的例子记为7,12,12,12,14即可
	//这样对于一个有序数组，我们每次二分查找>=sum-k的数字即可，使用lower_bound
	vector<ll> presum;
	presum.emplace_back(0);
	int ans = 0;
	ll sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += a[i];
		/*if (sum <= k)
		{
			ans = max(ans, i);
			continue;
		}*/
		auto it = lower_bound(presum.begin(), presum.end(), sum - k);
		if (it != presum.end())
		{
			int id = it - presum.begin();
			ans = max(ans, i - id);
		}
		presum.emplace_back(max(sum, presum[presum.size() - 1]));
	}
	cout << ans << '\n';
	return 0;
}