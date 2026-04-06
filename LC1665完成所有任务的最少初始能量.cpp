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
    static bool cmp(const vector<int>& x, const vector<int>& y) {
        return (x[1] - x[0]) < (y[1] - y[0]);
    }
    int minimumEffort(vector<vector<int>>& tasks) {
        auto& a = tasks;
        int n = a.size();
        sort(a.begin(), a.end(), cmp);
        //考虑逆推，从最后一步出发，a[i][1]-a[i][0]是做完这个任务剩余的能量
        //从最后一步来看，剩余的都没被使用，我们希望剩余的越少越好
        //因此按照剩余量排序
        //同时，逆推的过程中积累的一些电量，有利于加上上一步所需的能量，大于上一步的启动能量
        //这样一来额外付出的更少
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans + a[i][0], a[i][1]);
        }
        return ans;
    }
};