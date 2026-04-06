#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        //反悔贪心
        //先根据结束日期排序，结束日期越晚的，我们可以在后面去考虑，因为限制条件宽松
        //由于每门课程贡献都是1，花费时间越长的越不划算
        sort(courses.begin(), courses.end(), cmp);
        //优先队列维护当前选择的每个课的时长代价
        //遍历时，一旦遇到无法完成的课，
        //我们检查能否删除当前堆中最大的代价，把这个时长给当前这个课程，
        //能这么做的条件是当前课的时长<=堆顶的最大值值
        //这样做一定成立，假设我们来到位置i，前面的所有代价之和一定小于等于lastday[i-1]
        //lastday我们进行了降序排序，因此代价之和小于等于lastday[i]
        //此时替换一定是可以使得当前课被选择，并且此时进行替换之后，总贡献不变
        //多出了时间，在后续的遍历中，更有机会上完更多的课程
        int d = 0;
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            if (d + courses[i][0] <= courses[i][1]) {
                d += courses[i][0];
                pq.emplace(courses[i][0]);
            }
            else if (!pq.empty() && courses[i][0] <= pq.top()) {
                d -= pq.top();
                pq.pop();
                d += courses[i][0];
                pq.emplace(courses[i][0]);
            }
        }
        return pq.size();
    }
};