#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
int n;
vector<int> a;
//dp[i]表示i开头的最长递增子序列的长度
vector<int> dp;
vector<int> eds;
vector<int> ans;
int bs(int tar) {
    if (eds.empty()) return -1;
    int l = 0, r = eds.size() - 1;
    int ret = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (eds[mid] <= tar) {
            ret = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ret;
}
void lis() {
    for (int i = n; i >= 1; i--) {
        //每次找小于等于a[i]的最左侧位置
        //构建的ends数组是递减的，反向找最长递减子序列，正向就是最长递增子序列
        int pos = bs(a[i]);
        if (pos == -1) {
            eds.emplace_back(a[i]);
            dp[i] = eds.size();
        }
        else {
            eds[pos] = a[i];
            dp[i] = pos + 1;
        }
    }
}
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    lis();
    //正向构建答案
    //跟据我们求最长递增子序列，
    //得知:在两个数字对应的dp值相等的情况下，后面的一定小于等于前面的数
    //因此能更新就更新
    int n1 = 1;
    for (int i = 1; i <= n; i++) {
        n1 = max(n1, dp[i]);
    }
    ans.assign(n1 + 1, INF);
    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > ans[n1 - dp[i]]) {
            ans[n1 + 1 - dp[i]] = a[i];
        }
    }
    for (int i = 1; i <= n1; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}