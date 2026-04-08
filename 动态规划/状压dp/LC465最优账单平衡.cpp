/*
给你一个表示交易的数组 transactions ，
其中 transactions[i] = [from_i, to_i, amount_i] 
表示 ID = from_i 的人给 ID = to_i 的人共计 amount_i
请你计算并返回还清所有债务的最小交易笔数。

提示：
1 <= transactions.length <= 8
transactions[i].length == 3
0 <= from_i, to_i < 12
from_i != to_i
1 <= amounti <= 100
*/
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class Solution {
public:
    //对于一个n个元素集合(所有元素累加和为0)而言，最多需要操作的次数为n-1次
    //我们可以每次满足那个最小的元素，直到剩下两个元素，一次操作即可
    //类似于置换环
    //我们将这样的集合称之为不可再拆分的集合
    //我们需要将整个集合全部划分为多个不可再拆分的集合，这样是最优的
    //假设我们拆出来x个集合，由于每个集合(n个元素)操作次数为n-1
    //那么整体操作次数即为n-x
    //问题就转化为了，计算数组中要划分为不可拆分的累加和为0的子集，能划分出多少个
    //我们希望操作次数尽量小，就需要划分的子集数尽量多
    //在一个集合中，我们能拆则拆，这样就都是不可划分的
    vector<int> a;
    vector<int> dp;
    //dfs返回最大划分数
    //dp表只需要开一维，因为sum再次被表示集合状态的status唯一确定
    //status中0表示已经被使用，1表示尚未被使用
    int dfs(int status,int sum,int n)
    {
        if (dp[status] != -1) return dp[status];
        //如果集合中只剩一个元素，由于元素都不是0，所以划分出0个
        if ((status & (status - 1)) == 0)
        {
            return 0;
        }
        int ans = 0;
        if ((status & (status - 1)) != 0)
        {
            //如果状态中不只有1个1
            //讨论sum是否为0,
            //尝试策略是在数组中钦定一个元素属于一个集合，看看其他如何划分能使得划分数量最大
            //如果sum为0，我们找出一个任意元素来，这个元素需要占一个，再递归划分
            if (sum == 0)
            {
                for (int i = 0; i < n; i++)
                {
                    if (status & (1 << i))
                    {
                        ans = 1 + dfs(status ^ (1 << i), sum - a[i], n);
                    }
                    break;
                }
            }
            else {
                //如果sum不等于0,我们枚举每一个集合中的可用元素，看最多划分出几个
                for (int i = 0; i < n; i++)
                {
                    if (status & (1 << i))
                    {
                        ans =max(ans, 1 + dfs(status ^ (1 << i), sum - a[i], n));
                    }
                }
            }

        }
        dp[status] = ans;
        return ans;
    }
    int minTransfers(vector<vector<int>>& transactions) {
        int n = transactions.size();
        vector<int> a0(12, 0);
        for (int i = 0; i < n; i++)
        {
            int u = transactions[i][0], v = transactions[i][1], w = transactions[i][2];
            a0[u] -= w, a0[v] += w;
        }
        //目前得到了长度最大为12的数组a，我们想知道最少几次操作能使得数组中元素都变为0
        //显然，如果数组中元素已经是0，那么我们无需再操作
        //又知道：数组中所有元素的和为0
        for (int i = 0; i < 12; i++)
        {
            if (a0[i] != 0)
            {
                a.emplace_back(a0[i]);
            }
        }
        int n1 = a.size();
        dp.assign((1 << n1), -1);
        return n1 - dfs((1 << n) - 1, 0, n1);
    }
};