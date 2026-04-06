#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        auto& a = nums;
        int n = nums.size();
        if (is_sorted(a.begin(), a.end())) return 0;
        //O(n)的实现
        //类似于接雨水的思路，我们找出两侧满足条件的数字，这些一定是不用重新排序的
        //具体地，从左往右遍历，维护当前最大值，一旦遍历到的数字小于当前最大值，那么标记为需要重排
        //找到最右侧的需要重排的位置，该位置右侧的数字一定是不用重排的
        //从右向左同理
        int ans = 0;
        int m1 = -INF, pos1 = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] < m1) pos1 = i;
            else m1 = a[i];
        }
        ans += n - pos1 - 1;
        int m2 = INF, pos2 = n;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > m2) pos2 = i;
            else m2 = a[i];
        }
        ans += pos2;
        return n - ans;
    }
};