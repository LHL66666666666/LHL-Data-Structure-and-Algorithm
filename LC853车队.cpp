/*
在一条单行道上，有 n 辆车开往同一目的地。目的地是几英里以外的 target 。

给定两个整数数组 position 和 speed ，长度都是 n ，其中 position[i] 是第 i 辆车的位置， speed[i] 是第 i 辆车的速度(单位是英里/小时)。

一辆车永远不会超过前面的另一辆车，但它可以追上去，并以较慢车的速度在另一辆车旁边行驶。

车队 是指并排行驶的一辆或几辆汽车。车队的速度是车队中 最慢 的车的速度。

即便一辆车在 target 才赶上了一个车队，它们仍然会被视作是同一个车队。

返回到达目的地的车队数量 。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    static bool cmp(pair<int, int> a, pair<int, int> b)
    {
        return a.first > b.first;
    }
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        //后面的车不会超过前面的
        //先根据初始位置排序
        int n = position.size();
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)
        {
            a[i].first = position[i];
            a[i].second = speed[i];
        }
        sort(a.begin(), a.end(), cmp);
        //我们考虑到达终点的时间，如果一个车到达终点的时间大于前一辆
        //即位置更靠前的一辆，那么它应当被合并到前一个队伍，反之开一个新队伍
        double pre = (target - a[0].first) * 1.0 / a[0].second;
        double cnt = 1;
        for (int i = 1; i < n; i++)
        {
            double cur= (target - a[i].first) * 1.0 / a[i].second;
            if (cur > pre)
            {
                cnt++;
                pre = cur;
            }
        }
        return cnt;
    }
};