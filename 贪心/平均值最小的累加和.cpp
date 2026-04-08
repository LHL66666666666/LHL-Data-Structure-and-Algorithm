#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    //贪心策略是前k-1个最小的元素单独成为1组，剩下的数组成一组
    //这样一来，前k-1个确实找到了各自最小的平均数
    //把大数集中在一起，虽然平均值高，但只算一次；而小数单独成组，贡献极小。
    //如果把小数和大数混合，会导致小数组的平均值被拉高，反而增加总和
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for (int i = 1; i <= k - 1; i++) ans += a[i];
    ll sum = 0;
    for (int i = k; i <= n; i++) sum += ans;
    ans += sum / (n - k + 1);
    cout << ans << '\n';
    return 0;
}
/*
平均值最小累加和
给定一个长度为n的数组a
给定正整数k，要求将a划分为k个非空集合，每个数字只能进入一个集合，
返回每个集合的平均值累加起来的最小值(平均数向下取整)
1<=n<=1e5
0<=a[i]<=1e5
1<=k<=n
*/