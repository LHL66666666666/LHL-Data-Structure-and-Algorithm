/*
一张桌子上总共有 n 个硬币 栈 。每个栈有 正整数 个带面值的硬币。
每一次操作中，你可以从任意一个栈的 顶部 取出 1 个硬币，从栈中移除它，并放入你的钱包里。
给你一个列表 piles ，其中 piles[i] 是一个整数数组，分别表示第 i 个栈里 从顶到底 的硬币面值。
同时给你一个正整数 k ，请你返回在 恰好 进行 k 次操作的前提下，你钱包里硬币面值之和 最大为多少 。
*/
//转化很妙！！
/*
注意：对于本题来说，由于元素值都是非负数，且一定可以选 k 个硬币，
所以「至多」和「恰好」计算出来的结果是一样的。为方便写代码这里用至多
因为非负数我们取得越多越好，而且本题一定能取到k个(因为硬币总量>k)因此可以使用至多的定义方法
*/
#include<vector>
using namespace std;
class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int n = piles.size();
        //分析：由于是一个栈，每次只能从上面取，
        //对于一个栈（数组），我们只能移除其前缀
        //因此我们讨论在每一个栈中取几个元素
        //背包容量是k
        //先计算每个数组前缀和
        for (int i = 0; i < n; i++)
        {
            int n1 = piles[i].size();
            for (int j = 1; j < n1; j++)
            {
                piles[i][j] += piles[i][j - 1];
            }
        }
        //每个前缀和对应下标i，表示选这个位置的元素要花费i+1容量
        //每组里面只能选1个，就转化为了分组背包问题
        //dp[i][j]表示在1-i组上选择，花费代价j得到的最大价值
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        for (int i = 1; i <= n; i++)
        {
            int id1 = i - 1;
            for (int j = 0; j <= k; j++)
            {
                //不选
                dp[i][j] = dp[i - 1][j];
                //枚举每个位置该选哪个
                int n1 = piles[i - 1].size();
                for (int k = 0; k < n1; k++)
                {
                    int cost = k + 1;
                    int idx = j - cost;
                    if (idx >= 0)
                    {
                        dp[i][j] = max(dp[i][j], dp[i - 1][idx] + piles[i - 1][k]);
                    }
                }
            }
        }
        return dp[n][k];
    }
};