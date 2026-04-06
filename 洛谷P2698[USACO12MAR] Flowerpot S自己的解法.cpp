#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
using namespace std;
map<int, pair<int, int>> mp;
int main()
{
    int n, d;
    cin >> n >> d;
    //答案是-1的时候，我们找到最大的y和最小的y，如果差值小于d，输出-1
    int maxy = INT_MIN;
    int miny = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (mp.count(x) != 0)
        {
            mp[x].first = max(mp[x].first, y);
            mp[x].second = min(mp[x].second, y);
        }
        else {
            mp[x].first = y;
            mp[x].second = y;
        }
        maxy = max(maxy, y);
        miny = min(miny, y);
    }
    if (maxy - miny < d)
    {
        cout << -1 << '\n';
        return 0;
    }
    //我们维护区间上的有效的y的最大值和最小值
    //最值之差就是我们希望的答案
    deque<int> max_dq, min_dq;
    //单调性：如果一个区间已经满足题意，那么它再向外扩充一定满足
    //因为向外扩充会使最大值更大，最小值更小，或不变
    //收缩区间则会使得更难满足要求
    //要求的是最小的区间
    //是用双指针来找区间
    //枚举右维护左，左不回退，左侧收缩直到无法满足要求
    //难点在于一个x坐标下没有雨水如何处理，
    //使用有序表map操作
    int m = mp.size();
    //cout << m << '\n';
    vector<int> xi;
    //使用迭代器
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        xi.push_back(it->first);
    }

    int ans = INT_MAX;
    for (int r = 0, l = 0; r < m; r++) {
        // 维护最大y的单调队列
        while (!max_dq.empty() && mp[xi[r]].first >= mp[xi[max_dq.back()]].first) {
            max_dq.pop_back();
        }
        max_dq.push_back(r);

        // 维护最小y的单调队列
        while (!min_dq.empty() && mp[xi[r]].second <= mp[xi[min_dq.back()]].second) {
            min_dq.pop_back();
        }
        min_dq.push_back(r);

        // 关键修正：先确保队列头部在窗口内
        while (!max_dq.empty() && max_dq.front() < l) max_dq.pop_front();
        while (!min_dq.empty() && min_dq.front() < l) min_dq.pop_front();

        // 当满足条件时，收缩左边界
        while (!max_dq.empty() && !min_dq.empty() &&
            mp[xi[max_dq.front()]].first - mp[xi[min_dq.front()]].second >= d) {
            ans = min(ans, xi[r] - xi[l]);

            l++;
            // 收缩后再次确保队列头部在窗口内
            while (!max_dq.empty() && max_dq.front() < l) max_dq.pop_front();
            while (!min_dq.empty() && min_dq.front() < l) min_dq.pop_front();
        }
    }

    if (ans == INT_MAX) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }
    return 0;
}