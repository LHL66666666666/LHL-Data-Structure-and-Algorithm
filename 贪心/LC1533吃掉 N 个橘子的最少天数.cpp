#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    //dp会超时
    //我们发现一点：每次/2或者/3一定比-1使得n减小得更快
    //因此倾向于选择/2或/3的做法
    map<int, int> dp;
    int dfs(int x) {
        if (dp.find(x) != dp.end()) return dp[x];
        int ans = INF;
        ans = min(dfs(x / 2) + x % 2, dfs(x / 3) + x % 3) + 1;
        return dp[x] = ans;
    }
    int minDays(int n) {
        dp[3] = 2;
        dp[2] = 2;
        dp[1] = 1;
        dp[0] = 0;
        return dfs(n);
    }
};