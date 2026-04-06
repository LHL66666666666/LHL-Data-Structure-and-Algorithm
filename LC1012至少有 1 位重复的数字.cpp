#include <vector>
#include <string>
using namespace std;
using ll = long long;
ll dp[10][2050][2][2];
class Solution {
public:
    ll dfs(string& s, int id, int status, int islim, int isnum)
    {
        if (id == s.size())
        {
            return isnum;
        }
        if (dp[id][status][islim][isnum] != -1) return dp[id][status][islim][isnum];
        ll ans = 0;
        //如果之前还没选过数字，这一位也可以不选
        if (isnum == 0)
        {
            ans += dfs(s, id + 1, status, 0, 0);
        }
        //如果这一位要选
        //如果被限制
        if (islim)
        {
            //如果被限制，看前面是否选过，决定首位能否选0
            if (isnum)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (status & (1LL << i)) {
                        if (i == s[id] - '0') ans += dfs(s, id + 1, status ^ (1LL << i), 1, 1);
                        else if (i < s[id] - '0') ans += dfs(s, id + 1, status ^ (1LL << i), 0, 1);
                    }
                }
            }
            else {
                for (int i = 1; i < 10; i++)
                {
                    if (status & (1LL << i)) {
                        if (i == s[id] - '0') ans += dfs(s, id + 1, status ^ (1LL << i), 1, 1);
                        else if (i < s[id] - '0') ans += dfs(s, id + 1, status ^ (1LL << i), 0, 1);
                    }
                }
            }
        }
        //不被限制
        else {
            //看前面是否选过数字
            if (isnum)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (status & (1LL << i)) ans += dfs(s, id + 1, status ^ (1LL << i), 0, 1);
                }
            }
            else {
                for (int i = 1; i < 10; i++)
                {
                    if (status & (1LL << i)) ans += dfs(s, id + 1, status ^ (1LL << i), 0, 1);
                }
            }
        }
        dp[id][status][islim][isnum] = ans;
        return ans;
    }
    int countSpecialNumbers(int n) {
        //使用一个status压缩状态，表示还有哪些数字能使用，1表示可以使用的数字的位置
        string s;
        int tmp = n;
        while (tmp)
        {
            s += ('0' + tmp % 10);
            tmp /= 10;
        }
        reverse(s.begin(), s.end());
        memset(dp, -1, sizeof(dp));
        return dfs(s, 0, (1 << 10) - 1, 1, 0);
    }
    //跟LC2376统计特殊整数完全一样，至少1位重复的数字=n-各个数位上无重复的数字
    int numDupDigitsAtMostN(int n) {
        return n - countSpecialNumbers(n);
    }
};