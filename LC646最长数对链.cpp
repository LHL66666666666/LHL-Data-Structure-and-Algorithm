/*
给你一个由 n 个数对组成的数对数组 pairs ，其中 pairs[i] = [lefti, righti] 且 lefti < righti 。
现在，我们定义一种 跟随 关系，当且仅当 b < c 时，数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面。我们用这种形式来构造 数对链 。
找出并返回能够形成的 最长数对链的长度 。
你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    //在贪心优化之前，我们不妨先考虑原始的dp
    //原始的dp[i]表示i位置结尾(右端点结尾)的最长链
    //而我们要遍历找满足当前位置左端点>前面右端点的最长链
    //因此贪心优化的时候我们就ends数组记录右端点，每次查左端点
    //这样更好思考
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 1) return 1;
        //技巧：我们查询的数值和我们修改的数值是相互分离的
        //由于这个链要求首尾相接
        //我们在ends数组中存储的是右端点的值
        //每次查询时，我们要找>=这个新元素的左端点的最小值
        //跟据最长递增子序列LIS的思想
        //如果能将这个长度对应的右端点变得更小，就修改ends数组中的值
        //首先按照左端点排序，保证遍历顺序是按照左端点递增来的，这样才可能让数链更大
        sort(pairs.begin(), pairs.end());
        //ends数组记录的是右端点的数值
        vector<int> ends;
        for (int i = 0; i < n; i++)
        {
            //二分查找大于等于左端点的最小位置
            auto it = lower_bound(ends.begin(), ends.end(), pairs[i][0]);
            //如果不存在，那么加入新的
            if (it == ends.end())
            {
                ends.emplace_back(pairs[i][1]);
            }
            //如果存在，尝试更新
            else {
                int id = it - ends.begin();
                if (pairs[i][1] < ends[id])
                {
                    ends[id] = pairs[i][1];
                }
            }
        }
        return ends.size();
    }
};
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b)
    {
        return a[1] < b[1];
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        //最优解：贪心
        //我们按照右端点排序，维护一个当前右端点，遍历一遍，能接上的就接上
        //不需要考虑左端点
        int n = pairs.size();
        sort(pairs.begin(), pairs.end(), cmp);
        int ans = 0, pre = -0x3f3f3f3f;
        for (int i = 0; i < n; i++)
        {
            if (pairs[i][0] > pre)
            {
                pre = pairs[i][1];
                ++ans;
            }
        }
        return ans;
    }
};
//只要我们尽可能选取靠左的pair，就能得到最长的链。
//再仔细想一下，所谓的靠左其实和左边界没有关系，只和右边界有关系，
//那么我们就以右边界排序，顺次选取不重叠的pair的数量即可