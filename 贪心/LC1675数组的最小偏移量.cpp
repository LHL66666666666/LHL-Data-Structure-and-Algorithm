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
    int minimumDeviation(vector<int>& nums) {
        //注意到奇数只能乘1次2，但是偶数可以一直除以2直到变为奇数
        //有无限次数操作，我们先让每个奇数都*2达到最大值
        //然后再判断在这个数组中，所有数字在下降的过程中得到的最小值
        //每次只需要让最大值下降即可
        auto& a = nums;
        int n = a.size();
        multiset<int> s;
        for (int i = 0; i < n; i++) {
            if (a[i] & 1) s.insert(a[i] * 2);
            else s.insert(a[i]);
        }
        int ans = abs(*s.begin() - *s.rbegin());
        while (*s.rbegin() % 2 == 0) {
            auto it = s.rbegin();
            s.insert(*it / 2);
            s.erase(*it);
            ans = min(ans, abs(*s.begin() - *s.rbegin()));
        }
        return ans;
    }
};