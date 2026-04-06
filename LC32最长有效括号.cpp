#include <string>
using namespace std;
class Solution {
public:
    int dp[30005];
    int longestValidParentheses(string s) {
        int n = s.size();
        //定义dp[i]的状态表示以i结尾的最长有效括号子序列的长度
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                dp[i] = 0;
            }
            else {
                //右括号
                if (i - 1 >= 0)
                {
                    int move = dp[i - 1];
                    int pre = i - move - 1;
                    if (pre >= 0 && s[pre] == '(')
                    {
                        //能找到配对
                        if (pre - 1 >= 0)
                        {
                            dp[i] = 2 + dp[i - 1] + dp[pre - 1];
                        }
                        else dp[i] = 2 + dp[i - 1];
                    }
                    else {
                        //无配对或越界
                        dp[i] = 0;
                    }
                }
                else dp[i] = 0;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};