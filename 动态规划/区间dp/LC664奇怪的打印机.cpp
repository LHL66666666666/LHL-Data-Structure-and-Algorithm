#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int strangePrinter(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1,INF));
        //base case
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 1;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                {
                    dp[i][j] = dp[i + 1][j];
                }
                for (int k = i; k < j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};