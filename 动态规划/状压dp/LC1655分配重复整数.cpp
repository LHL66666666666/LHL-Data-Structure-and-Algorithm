#include <vector>
#include <map>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> a;
    vector<int> cnt;
    vector<vector<int>> dp;
    //dfs(status,i)表示当前来到i号元素，要满足状态为status，能否达成
    //本题的尝试是基于枚举：每个人需求的子集
    //我们计算出：
    //0001->val[0] 表示满足0号人需求所需的数量
    //0010->val[1] 表示满足1号人需求所需的数量
    //类似地，0011->val[0]+val[1] 表示满足0号人和1号人需求所需的数量
    //对于每个元素，我们尝试每种可以满足的子集
    int dfs(int status, int i, int m)
    {
        if (status == 0)
        {
            return 1;
        }
        if (i >= a.size())
        {
            return 0;
        }
        if (dp[status][i] != -1) return dp[status][i];
        //枚举status的子集
        //不使用，(实际上我们做了贪心优化之后，可以直接忽略这一步)
        int ans = dfs(status, i + 1,m);
        for (int j = status; j > 0; j = (j - 1) & status)
        {
            if (a[i] >= cnt[j])
            {
                ans |= dfs(status ^ j, i + 1, m);
            }
        }
        dp[status][i] = ans;
        return ans;
    }
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int n = nums.size();
        map<int, int> mp;
        for (int i = 0; i < n; i++)
        {
            mp[nums[i]]++;
        }
        for (auto& i : mp)
        {
            a.emplace_back(i.second);
        }
        sort(quantity.begin(), quantity.end());
        //这里排序实际上是贪心优化，对于大的数字，我们肯定是希望它一定要选，先去满足一些
        //对于小的数字，如果当前状态不是0，还没有能满足的，就直接返回0了
        sort(a.begin(), a.end(), greater<int>());
        //编号不重要，现在a中有n1种数字，已知各个数字的数量
        int n1 = a.size();
        int m = quantity.size();
        int s0 = (1 << m) - 1;
        cnt.resize(s0 + 1);
        for (int j = s0; j > 0; j = (j - 1) & s0)
        {
            int sum = 0;
            int tmp = j;
            for (int k = 0; k < m; k++)
            {
                if (tmp & (1 << k)) sum += quantity[k];
            }
            cnt[j] = sum;
        }
        dp.assign(s0 + 1, vector<int>(n1 + 1, -1));
        return dfs(s0, 0, m);
    }
};