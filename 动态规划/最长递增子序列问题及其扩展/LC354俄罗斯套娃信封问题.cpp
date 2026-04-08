/*
给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
注意：不允许旋转信封。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b)
    {
        //如果宽度不同，按宽度从小到大排序
        if (a[0] != b[0]) return a[0] < b[0];
        //相同宽度下，按高度从大到小排序
        return a[1] > b[1];
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 1) return 1;
        //排一下序
        sort(envelopes.begin(), envelopes.end(), cmp);
        //按照这样排完序之后,宽度信息就是无用的了
        //转化为找高度数组最长递增(严格递增)子序列
        //因为我们这样排序之后，保证宽度相同的组中高度不递增
        //这样就保证了高度的最长递增子序列的选取不会出现在一个宽度组内部
        //这样就满足了宽度严格增，高度严格增
        //同时，统一宽度组内部，高度递减，
        //保证了在遍历过程中高度可以贪心的选取最小的来更新ends数组
        vector<int> h;
        for (int i = 0; i < n; i++) h.emplace_back(envelopes[i][1]);
        //找h数组最长递增子序列即可
        vector<int> ends;
        ends.emplace_back(h[0]);
        for (int i = 1; i < n; i++)
        {
            auto it = lower_bound(ends.begin(), ends.end(), h[i]);
            if (it == ends.end())
            {
                ends.emplace_back(h[i]);
            }
            else {
                int id = it - ends.begin();
                ends[id] = h[i];
            }
        }
        return ends.size();
    }
};
//同时控制 w 和 h 两个维度并不是那么容易，
//因此我们考虑固定一个维度，再在另一个维度上进行选择