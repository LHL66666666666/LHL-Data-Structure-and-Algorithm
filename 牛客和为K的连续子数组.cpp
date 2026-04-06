/*
给定一个无序数组 arr , 其中元素可正、可负、可0。给定一个整数 k ，求 arr 所有连续子数组中累加和为k的最长连续子数组长度。保证至少存在一个合法的连续子数组。
[1,2,3]的连续子数组有[1,2]，[2,3]，[1,2,3] ，但是[1,3]不是
数据范围：
1≤n≤10^5
∣val∣≤100，
∣k∣≤10^9
要求：空间复杂度O(n) ， 时间复杂度O(n)
*/
#include <vector>
#include <unordered_map>
class Solution {
public:
    int maxlenEqualK(std::vector<int>& arr, int k) {
        //思想是按照每一个位置结尾来考虑，找到这个位置向前最长推多少才能使范围累加和达到目标
        //注意这个题目是有负数的，不能使用滑动窗口！！！
        int n = arr.size();
        //开一个哈希表记录某个前缀和的值最早出现的位置
        std::unordered_map<int, int> mp;
        //记得要插入0,-1表示前缀和为零最早在不加任何数字的时候出现过
        mp.insert({0,-1});
        for (int i = 1; i < n; i++)
        {
            //前缀和构建
            arr[i] += arr[i - 1];
        }
        for (int i = 0; i < n; i++)
        {
            if (mp.count(arr[i]) == 0)
            {
                mp.insert({ arr[i],i });
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            //目标是k，前缀和为arr[i]，k=arr[i]-arr[x]
            //arr[x]=arr[i]-k
            //注意要找的东西是什么
            if (mp.count(arr[i]-k) != 0)
            {
                if (mp[arr[i]-k] < i)
                {
                    ans = std::max(ans, i-mp[arr[i]-k]);
                }
            }
        }
        return ans;

    }
};