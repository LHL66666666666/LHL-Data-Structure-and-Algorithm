#include <vector>
#include <string>
using namespace std;
using ll = long long;
ll dp[35][2][2][2];
class Solution {
public:
    ll dfs(string& s, int id, int lst, int islim, int isnum)
    {
        if (id == s.size())
        {
            return isnum;
        }
        if (dp[id][lst][islim][isnum] != -1) return dp[id][lst][islim][isnum];
        ll ans = 0;
        if (isnum == 0)
        {
            ans += dfs(s, id + 1, 0, 0, 0);
        }
        if (islim)
        {
            if (isnum)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (i == 1 && lst == 1) continue;
                    if (i + '0' < s[id])
                    {
                        ans += dfs(s, id + 1, i, 0, 1);
                    }
                    else if (i + '0' == s[id])
                    {
                        ans += dfs(s, id + 1, i, 1, 1);
                    }
                }
            }
            else {
                for (int i = 1; i < 2; i++)
                {
                    if (i == 1 && lst == 1) continue;
                    if (i + '0' < s[id])
                    {
                        ans += dfs(s, id + 1, i, 0, 1);
                    }
                    else if (i + '0' == s[id])
                    {
                        ans += dfs(s, id + 1, i, 1, 1);
                    }
                }
            }
        }
        else {
            if (isnum)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (i == 1 && lst == 1) continue;
                    ans += dfs(s, id + 1, i, 0, 1);
                }
            }
            else {
                for (int i = 1; i < 2; i++)
                {
                    if (i == 1 && lst == 1) continue;
                    ans += dfs(s, id + 1, i, 0, 1);
                }
            }
        }
        dp[id][lst][islim][isnum] = ans;
        return ans;
    }
    int findIntegers(int n) {
        if (n == 1) return 2;
        string s;
        int flag = 0;
        for (int i = 31; i >= 0; i--)
        {
            if (n & (1LL << i))
            {
                flag = 1;
            }
            if (flag)
            {
                s.push_back(((n >> i) & 1) + '0');
            }
        }
        memset(dp, -1, sizeof(dp));
        return dfs(s, 0, 0, 1, 0) + 1;
    }
};