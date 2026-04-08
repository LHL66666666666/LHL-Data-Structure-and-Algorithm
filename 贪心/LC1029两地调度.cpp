#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;
class Solution {
public:
    struct node {
        int a, b, diff;
    };
    static bool cmp(node x, node y) {
        return x.diff < y.diff;
    }
    int twoCitySchedCost(vector<vector<int>>& costs) {
        //每个人都需要去一个城市，跟据花费的差值来排序
        int n = costs.size();
        vector<node> v(n);
        for (int i = 0; i < n; i++) {
            v[i].a = costs[i][0], v[i].b = costs[i][1];
            v[i].diff = costs[i][0] - costs[i][1];
        }
        sort(v.begin(), v.end(), cmp);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i < n / 2) ans += v[i].a;
            else ans += v[i].b;
        }
        return ans;
    }
};