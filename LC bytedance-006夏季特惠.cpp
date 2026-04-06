/*
某公司游戏平台的夏季特惠开始了，你决定入手一些游戏。现在你一共有X元的预算，
该平台上所有的 n 个游戏均有折扣，标号为 i 的游戏的原价 ai元，
现价只要 bi 元（也就是说该游戏可以优惠 ai−bi 元）
 并且你购买该游戏能获得快乐值为wi
 ​由于优惠的存在，你可能做出一些冲动消费导致最终买游戏的总费用超过预算，
 但只要满足获得的总优惠金额不低于超过预算的总金额，那在心理上就不会觉得吃亏。
 现在你希望在心理上不觉得吃亏的前提下，获得尽可能多的快乐值。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
struct node {
	ll a, b, w, diff;
};
//dp[i][j]表示，前i个物品自由选择，花费预算不超过j
ll dp[505][100005];
int main()
{
	int n, x;
	cin >> n >> x;
	vector<node> v(1);
	//每买一个，花费b，就让预算增加diff
	//实际上，每次真正花费的钱数为原价-优惠
	//如果这个数值小于0，就直接加上(必须买的)
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		int diff = a - b;
		//先扩展预算，计算出必须选择的
		if (b - diff <= 0)
		{
			x -= (b - diff);
			ans += w;
		}
		else v.push_back({ a,b,w,a - b });
	}
	//再跑01背包
	int n1 = v.size();
	for (int i = 1; i < n1; i++)
	{
		int c = v[i].b - v[i].diff;
		int w = v[i].w;
		for (int j = 0; j <= x; j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (j - c >= 0)
			{
				dp[i][j] = max(dp[i][j], dp[i - 1][j - c] + w);
			}
		}
	}
	cout << ans+dp[n1-1][x] << '\n';
	return 0;
}