#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
struct node {
    ll l, r, val;
};
const int INF = 0x3f3f3f3f;
bool cmp(node x, node y)
{
    if (x.r != y.r) return x.r < y.r;
    return x.l < y.l;
}
class Solution {
public:
    vector<ll> dp;
    vector<int> end;
    vector<node> a;
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        //将所有工作按照结束时间升序排序
        int n = profit.size();
        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            a[i].l = startTime[i];
            a[i].r = endTime[i];
            a[i].val = profit[i];
        }
        sort(a.begin(), a.end(), cmp);
        for (int i = 0; i < n; i++) end.emplace_back(a[i].r);
        dp.assign(n + 1, 0);
        //dp[i]表示按照结束时间排序之后，前i个工作能获得的最大的收益
        dp[0] = a[0].val;
        for (int i = 1; i < n; i++)
        {
            //两种选择，第一种是不做i位置结尾的工作
            dp[i] = dp[i - 1];
            //第二种是要做第i位置结尾的工作，
            //那么就需要二分查找它开始时间在这一堆结束时间中的位置
            auto it = upper_bound(end.begin(), end.end(), a[i].l) - end.begin();
            if (it == 0)
            {
                //因为我们找的是upper_bound严格大于的位置
                //如果找到0证明这个开始时间比0位置的结束时间更加靠前
                dp[i] = max(dp[i], a[i].val);
            }
            else {
                dp[i] = max(dp[i], dp[it-1] + a[i].val);
            }
        }
        return dp[n - 1];
    }
};