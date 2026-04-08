#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    //先写递归
    int f1(vector<int>& cur, int l, int r, vector<vector<int>>& dp)
    {
        if (dp[l][r] != -1) return dp[l][r];
        if (l >= r) return 0;
        if (r - l == 1)
        {
            return 0;
        }
        int ans = INF;
        for (int i = l + 1; i < r; i++)
        {
            int tmp = cur[r] - cur[l];
            tmp += f1(cur, l, i,dp) + f1(cur, i, r,dp);
            ans = min(ans, tmp);
        }
        dp[l][r] = ans;
        return ans;
    }
    int minCost(int n, vector<int>& cuts) {
        vector<int> cur;
        cur.emplace_back(0);
        int m = cuts.size();
        for (int i = 0; i < m; i++)
        {
            cur.emplace_back(cuts[i]);
        }
        cur.emplace_back(n);
        int n1 = cur.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n1 + 1, -1));
        //难绷，给出的竟然不是有序的
        sort(cur.begin(), cur.end());
        return f1(cur, 0, n1 - 1,dp);
    }
};

class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int minCost(int n, vector<int>& cuts) {
        vector<int> cur;
        cur.emplace_back(0);
        int m = cuts.size();
        for (int i = 0; i < m; i++)
        {
            cur.emplace_back(cuts[i]);
        }
        cur.emplace_back(n);
        sort(cur.begin(), cur.end());
        int n1 = cur.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n1 + 1));
        for (int i = n1 - 1; i >= 0; i--)
        {
            for (int j = i; j <= min(n1 - 1, i + 1); j++)
            {
                dp[i][j] = 0;
            }
        }
        for (int i = n1 - 1; i >= 0; i--)
        {
            for (int j = i + 2; j <= n1 - 1; j++)
            {
                dp[i][j] = INF;
                for (int k = i + 1; k < j; k++)
                {
                    int tmp = cur[j] - cur[i];
                    tmp += dp[i][k] + dp[k][j];
                    dp[i][j] = min(dp[i][j], tmp);
                }

            }
        }
        return dp[0][n1 - 1];
    }
};