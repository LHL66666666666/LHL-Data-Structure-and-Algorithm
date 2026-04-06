#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int n, m;
    vector<vector<int>> dp;
    int dfs(string& a,string& b,int i, int j)
    {
        if (j == m)
        {
            return 0;
        }
        if (dp[i][j] != -1) return dp[i][j];
        int ans = INF;
        if (a[i] == b[j])
        {
            ans = 1 + dfs(a, b, i, j + 1);
        }
        else {
            //不能直接往左和往右dfs，会产生很多重复状态
            //遍历找到所有匹配的
            for (int k = 0; k < n; k++)
            {
                if (a[k] == b[j])
                {
                    ans = min(ans, min(abs(k - i), n - abs(k - i)) + dfs(a, b, k, j));
                }
            }
        }
        dp[i][j] = ans;
        return ans;
    }
    int findRotateSteps(string ring, string key) {
        n = ring.size(), m = key.size();
        //显然，每次的抉择就是要么顺时针转，要么逆时针转，直到匹配所有的key的字符
        //步数一定不会超过100*100次
        //dp[i][j]表示ring来到i位置，可以匹配完字符串key从j位置到结尾的最小步数
        dp.assign(n + 1, vector<int>(m + 1, -1));
        return dfs(ring, key, 0, 0);
    }
};

//贪心优化
//实际上，如果当前来到ring的i位置，要满足的key中的字符为x(目前二者不匹配)
//我们不需要遍历找所有匹配的位置，只需要找i位置左右最近的x字符即可
//为了快速查询，我们预处理出每个字符出现的所有下标，
//对于i位置，我们在x字符的下标集合中，二分查找大于i的和小于i的第一个位置(注意是环形数组)
//即可将枚举优化到log时间
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int n, m;
    vector<vector<int>> dp;
    vector<vector<int>> g;
    int dfs(string& a, string& b, int i, int j)
    {
        if (j == m)
        {
            return 0;
        }
        if (dp[i][j] != -1) return dp[i][j];
        int ans = INF;
        if (a[i] == b[j])
        {
            ans = 1 + dfs(a, b, i, j + 1);
        }
        else {
            //二分查找到i位置左和右的最近的下标
            int x = b[j] - 'a';
            int n1 = g[x].size();
            int l = -1, r = -1;
            if (i > g[x][n1 - 1])
            {
                l = g[x][n1 - 1], r = g[x][0];
            }
            else if (i < g[x][0])
            {
                l = g[x][n1 - 1], r = g[x][0];
            }
            else {
                auto it = upper_bound(g[x].begin(), g[x].end(), i) - g[x].begin();
                l = g[x][it - 1], r = g[x][it];
            }
            //只需要两种可能性展开,l和r
            ans = min(ans, min(abs(l - i), n - abs(l - i)) + dfs(a, b, l, j));
            ans = min(ans, min(abs(r - i), n - abs(r - i)) + dfs(a, b, r, j));
        }
        dp[i][j] = ans;
        return ans;
    }
    int findRotateSteps(string ring, string key) {
        n = ring.size(), m = key.size();
        dp.assign(n + 1, vector<int>(m + 1, -1));
        g.resize(26);
        //遍历的时候我们已经保证了g[i]是有序的
        for (int i = 0; i < n; i++)
        {
            g[ring[i] - 'a'].emplace_back(i);
        }
        return dfs(ring, key, 0, 0);
    }
};