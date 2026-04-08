/*
给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，
然后该子数组（剩下）的元素总和是所有子数组之中最大的。
注意，删除一个元素后，子数组 不能为空。
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    int dp[100005][2];
    const int INF = 0x3f3f3f3f;
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];
        //特判全是负数的
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] >= 0) flag = 1;
        }
        if (!flag)
        {
            int ret = -INF;
            for (int i = 0; i < n; i++)
            {
                ret = max(ret, arr[i]);
            }
            return ret;
        }
        //删除操作实际上相当于将这个位置元素变为0
        //dp[i][0]表示到i位置没删除元素，取得的子数组最大和
        //dp[i][1]表示到i位置已经删除过一次元素，取得的子数组最大和
        dp[0][0] = arr[0];
        dp[0][1] = 0;
        for (int i = 1; i < n; i++)
        {
            //如果不删，那么就是子数组最大和
            dp[i][0] = max(dp[i - 1][0] + arr[i], arr[i]);
            //如果要删，要么删自己，要么删前面的，二者取最大值
            dp[i][1] = max(dp[i - 1][1] + arr[i], dp[i - 1][0]);
        }
        int ans = -INF;
        for (int i = 0; i < n; i++)
        {
            ans = max(dp[i][0], ans);
            ans = max(dp[i][1], ans);
        }
        return ans;
    }
};
class Solution {
public:
    int dp[100005][2];
    const int INF = 0x3f3f3f3f;
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];
        //删除操作实际上相当于将这个位置元素变为0
        //dp[i][0]表示到i位置没删除元素
        //dp[i][1]表示到i位置已经删除过元素
        dp[0][0] = arr[0];
        dp[0][1] = 0;
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0] + arr[i], arr[i]);
            dp[i][1] = max(dp[i - 1][1] + arr[i], dp[i - 1][0]);
        }
        int ans = dp[0][0];
        for (int i = 1; i < n; i++)
        {
            ans = max(dp[i][0], ans);
            ans = max(dp[i][1], ans);
        }
        return ans;
    }
};