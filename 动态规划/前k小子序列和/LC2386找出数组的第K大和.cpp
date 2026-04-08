/*
给你一个整数数组 nums 和一个 正 整数 k 。你可以选择数组的任一 子序列 并且对其全部元素求和。
数组的 第 k 大和 定义为：可以获得的第 k 个 最大 子序列和（子序列和允许出现重复）
返回数组的 第 k 大和 。
子序列是一个可以由其他数组删除某些或不删除元素派生而来的数组，且派生过程不改变剩余元素的顺序。
注意：空子序列的和视作 0 。
*/
#include<vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
auto cmp = [](const pair<ll, int>& a, const pair<ll, int>& b)
    {
        return a.first > b.first;
    };
class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        //转化：由于数组中允许存在负数
        //最大和就是全体非负数相加
        //更小的子序列和是有最大和减去某个正数，或者加上某个负数得来的
        //我们不妨对数组中全体元素取绝对值，那么就转化为求前k小的子序列和
        //最大和减去这前k小子序列和就是前k大子序列和
        int n = nums.size();
        ll sum = 0;
        for (int i = 0; i < n; i++) if (nums[i] > 0) sum += nums[i];
        //取绝对值
        for (int i = 0; i < n; i++) if (nums[i] < 0) nums[i] = -nums[i];
        //排序，使用堆找前k小和
        sort(nums.begin(), nums.end());
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(cmp)> pq(cmp);
        pq.emplace(nums[0],0);
        vector<ll> ret;
        //空集
        ret.emplace_back(0);
        while (ret.size() < k)
        {
            auto tmp = pq.top();
            pq.pop();
            ll s = tmp.first;
            int id = tmp.second;
            ret.emplace_back(s);
            if (id + 1 < n)
            {
                pq.emplace(s + nums[id + 1], id + 1);
                pq.emplace(s - nums[id] + nums[id + 1], id + 1);
            }
        }
        return sum - ret[k - 1];
    }
};
/*
把这道题转化为最短路模型，可以帮助理解结果为什么是对的（可以直接用 dijkstra 算法的正确性保证本题堆解法的正确性）。
首先，假设所有元素都是正数（非全为正数情形可以转化为全为正数情形），
并且所求是第 k 小子集和（第 k 大子集和可以转化为第 k 小子集和），假设排序后的序列为 a_1 a_2 ... a_n。
把上述序列 a_1 a_2 ... a_n 的每个非空子序列 a_{p1} a_{p2} ... a_{pm} 都看作是一个节点，
将这个节点与子序列 a_{p1} a_{p2} ... a_{pm} a_{p_m+1}、a_{p1} a_{p2} ... a_{p_{m-1}} a_{p_m+1} 对应的节点连一条有向边，
边的权重分别为 a_{p_m+1}、a_{p_m+1} - a_{p_m}，则所有子序列对应的节点构成一个有向图，所有边的边权非负，
且子序列 a_1 对应的节点（源点）到任意一个子序列对应的节点都存在一条路径，路径长度为子序列的和减 a_1。
本题的堆解法可以看作是在这个图上跑 dijkstra 算法
*/