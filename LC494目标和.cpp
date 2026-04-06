#include<vector>
using namespace std;
class Solution {
public:
    const int offset = 1000;
    const int INF = 0x3f3f3f3f;
    //状态定义：dp[i][j]表示到i位置，累加和为j的表达式的数量
    //注意：累加和我们统一偏移量offset(向右偏移)，保证下标非负
    int dp1[25][2005];
    //从递归开始
    int findTargetSumWays1(vector<int>& nums, int target) {
        return f1(nums, 0, 0, target);
    }
    int f1(vector<int>& nums, int id, int sum, int tar)
    {
        int n = nums.size();
        if (id == n)
        {
            return sum == tar;
        }
        return f1(nums, id + 1, sum + nums[id], tar) + f1(nums, id + 1, sum - nums[id], tar);
    }
    //记忆化搜素
    int findTargetSumWays2(vector<int>& nums, int target) {
        memset(dp1, -1, sizeof(dp1));
        return f2(nums, 0, offset, target);
    }
    int f2(vector<int>& nums, int id, int sum, int tar)
    {
        int n = nums.size();
        if (id == n)
        {
            return sum == tar + offset;
        }
        if (dp1[id][sum] != -1) return dp1[id][sum];
        int ans = 0;
        ans = f2(nums, id + 1, sum + nums[id], tar) + f2(nums, id + 1, sum - nums[id], tar);
        dp1[id][sum] = ans;
        return ans;
    }
    //位置依赖的dp,需要从结尾位置出发找0,0时的状态
    //因为base case在结尾处
    int dp[25][20005];
    //使用offset来处理偏移
    //实际的和是[-offset,offset]
    //偏移之后变为[0,2*offset+1]
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        //第n行
        dp[n][target + offset] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            //每一行依赖于上一行
            //s表示原始的和
            //核心是先计算原来的和，最后再统一偏移
            for (int s = -offset; s <= offset; s++)
            {
                //j是偏移之后的和
                int j = s + offset;
                dp[i][j] = 0;
                //先计算原来的和，再偏移
                int lst1 = s + nums[i] + offset;
                int lst2 = s - nums[i] + offset;
                if (lst1 >= 0 && lst1 <= 2*offset)
                {
                    dp[i][j] += dp[i + 1][lst1];
                }
                if (lst2 >= 0 && lst2 <= 2*offset)
                {
                    dp[i][j] += dp[i + 1][lst2];
                }
            }

        }
        //原本要找的是0，0的状态，也就是到0位置，和为0的状态，
        //和被偏移之后变为0+offset
        return dp[0][offset];
    }
};
//最优解：转化为01背包问题
//观察：
//1）首先，数组中每一个值都可以取+或-，也就是说，可以将整个数组全体元素看作正数
//2）整个问题就相当于将数组划分为两个集合A,B,集合A取正，集合B取负，然后相加
//也就是说我们需要sumA-sumB=target,而整个集合的sum=sumA+sumB
//转化一下，sumA-(sum-sumA)=target  -->  sumA=(target+sum)/2
//但是我们不能让这里出现除法被截断，因此target+sum必须是一个偶数，换言之target和sum奇偶性要相同，
//否则不存在这样的sumA(因为带0.5)
//3)由此我们就转化为01背包问题，我们要在整个集合中选若干个数字，使得和为sumA
//就变成了一个01背包问题
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
        }
        //注意特判，防止开一个负数的vector
        if (abs(target) > sum)
        {
            return 0;
        }
        //判奇偶性是否一致
        if (((sum & 1) ^ (target & 1)) != 0)
        {
            return 0;
        }
        int s = (target + sum) / 2;
        //01背包
        //状态定义：dp[i][j]表示前i个元素自由选择，达到j价值的方案数
        vector<vector<int>> dp(n + 1, vector<int>(s + 1));
        //注意base case,一个数字也不选是空集，能得到总和为0的
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            //每个位置选或者不选的方案数量应该相加
            for (int j = 0; j <= s; j++)
            {
                //不选
                dp[i][j] = dp[i - 1][j];
                if (j - nums[i - 1] >= 0)
                {
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][s];
    }
};