#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
class Solution {
public:
    struct node {
        int q, w;
        double sig;
    };
    static bool cmp(const node& x, const node& y) {
        return x.sig < y.sig;
    }
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        auto& q = quality;
        auto& w = wage;
        int n = q.size();
        vector<node> a(n);
        for (int i = 0; i < n; i++) {
            a[i].q = q[i];
            a[i].w = w[i];
            a[i].sig = (double)a[i].w / a[i].q;
        }
        //单位工资大的一定能满足所有比自己单位工资小的工人的期望
        //单位工资小的一定不能满足比自己单位工资大的人
        //枚举作为单位工资的人
        sort(a.begin(), a.end(), cmp);
        //需要维护从k-1到n-1下标对应的数字，前面数字中选k-1个，累加和最小
        vector<ll> sum(n);
        priority_queue<ll> pq;
        ll cur = 0;
        for (int i = 0; i < n; i++) {
            if (pq.size() < k - 1) {
                cur += a[i].q;
                pq.emplace(a[i].q);
            }
            else {
                sum[i] = a[i].q + cur;
                pq.emplace(a[i].q);
                cur += a[i].q;
                cur -= pq.top();
                pq.pop();
            }
        }
        double ans = INF;
        for (int i = n - 1; i >= k - 1; i--) {
            ans = min(ans, a[i].sig * sum[i]);
        }
        return ans;
    }
};