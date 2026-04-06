#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
class Solution {
public:
    int numTilings(int n) {
        //dp[i]=dp[i-1]+dp[i-2]+2*(dp[i-3]+dp[i-4]+...+dp[1]+1)
        //dp[i-1]=dp[i-2]+dp[i-3]+2*(dp[i-4]+...+dp[1]+1)
        //×÷²î£ºdp[i]-dp[i-1]=dp[i-1]-dp[i-3]
        //dp[i]=2*dp[i-1]+dp[i-3]
        vector<ll> dp(1005);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;
        for (int i = 4; i <= n; i++) {
            dp[i] = 2LL * dp[i - 1] + dp[i - 3];
            dp[i] %= MOD;
        }
        return dp[n];
    }
};