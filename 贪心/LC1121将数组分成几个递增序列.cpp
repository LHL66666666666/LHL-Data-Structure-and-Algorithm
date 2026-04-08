#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        if (k == 1) return true;
        auto& a = nums;
        int n = a.size();
        //关键点：要求严格递增，子序列的个数不少于数组中最大词频的元素个数
        //因为相同元素必须出现在不同的子序列中
        //又：我们希望子序列长度尽量大，那么希望分的组尽量少，因此就分最大词频的元素个数组
        vector<int> cnt(100005);
        int x = 0;
        for (int i = 0; i < n; i++) {
            cnt[a[i]]++;
            x = max(x, cnt[a[i]]);
        }
        return n / x >= k;
    }
};
/*
给你一个 非递减 的正整数数组 nums 和整数 K，
判断该数组是否可以被分成一个或几个 长度至少 为 K 的 不相交的递增子序列。
*/