/*
给你一个下标从 0 开始包含 n 个正整数的数组 arr ，和一个正整数 k 。
如果对于每个满足 k <= i <= n-1 的下标 i ，都有 arr[i-k] <= arr[i] ，那么我们称 arr 是 K 递增 的。
比方说，arr = [4, 1, 5, 2, 6, 2] 对于 k = 2 是 K 递增的，因为：
arr[0] <= arr[2] (4 <= 5)
arr[1] <= arr[3] (1 <= 2)
arr[2] <= arr[4] (5 <= 6)
arr[3] <= arr[5] (2 <= 2)
但是，相同的数组 arr 对于 k = 1 不是 K 递增的（因为 arr[0] > arr[1]），对于 k = 3 也不是 K 递增的（因为 arr[0] > arr[3] ）。
每一次 操作 中，你可以选择一个下标 i 并将 arr[i] 改成任意 正整数。

请你返回对于给定的 k ，使数组变成 K 递增的 最少操作次数 。
*/
#include <vector>
using namespace std;
class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        //k这个数字将整个数组分成了最多k组
        //按照模k的余数来划分
        //每一组都要严格单调不减
        //且这k组是相互独立的
        //要改数字的最优策略是直接改为1
        vector<vector<int>> ends(k);
        //对每一组都跑一遍最长不下降子序列
        for (int i = 0; i < n; i++)
        {
            int id = i % k;
            auto it = upper_bound(ends[id].begin(), ends[id].end(), arr[i]);
            if (it == ends[id].end())
            {
                ends[id].emplace_back(arr[i]);
            }
            else {
                int id1 = it - ends[id].begin();
                ends[id][id1] = arr[i];
            }
        }
        int ans = 0;
        for (int i = 0; i < k; i++)
        {
            //每组有几个数字
            int num = n / k;
            if (i > n % k)++num;
            ans += num - ends[i].size();
        }
        return ans;
    }
};