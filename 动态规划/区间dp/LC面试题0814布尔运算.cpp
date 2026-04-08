#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    //先尝试递归
    int f(string& s, int l, int r, int tar, vector<vector<vector<int>>>& dp)
    {
        if (dp[l][r][tar] != -1) return dp[l][r][tar];
        //base case
        if (r - l == 0)
        {
            return s[l] - '0' == tar;
        }
        //枚举分割点(也就是最后一个被计算的运算符)
        int ret = 0;
        for (int i = l + 1; i < r; i += 2)
        {
            int tmp = 0;
            if (s[i] == '^')
            {
                if (tar == 1) {
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 1, dp));
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 0, dp));
                }
                else
                {
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 0, dp));
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 1, dp));

                }
            }
            else if (s[i] == '|')
            {
                if (tar == 1) {
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 1, dp));
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 0, dp));
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 1, dp));
                }
                else
                {
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 0, dp));
                }
            }
            else if (s[i] == '&')
            {
                if (tar == 1) {
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 1, dp));
                }
                else
                {
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 0, dp));
                    tmp += (f(s, l, i - 1, 1, dp) * f(s, i + 1, r, 0, dp));
                    tmp += (f(s, l, i - 1, 0, dp) * f(s, i + 1, r, 1, dp));
                }
            }
            ret += tmp;
        }
        dp[l][r][tar] = ret;
        return ret;
    }
    int countEval(string s, int result) {
        int n = s.size();
        if (n == 1)
        {
            return result == (s[0] - '0');
        }
        if (n == 3)
        {
            int l = 0, r = 2;
            int x = s[l] - '0', y = s[r] - '0';
            int ans = 0;
            if (s[l + 1] == '^') ans = x ^ y;
            else if (s[l + 1] == '|') ans = x | y;
            else if (s[l + 1] == '&') ans = x & y;
            return ans == result;
        }
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2,-1)));
        return f(s, 0, n - 1, result, dp);
    }
};