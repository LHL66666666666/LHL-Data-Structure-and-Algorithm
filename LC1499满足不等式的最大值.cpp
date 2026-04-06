/*
给你一个数组 points 和一个整数 k 。数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序。也就是说 points[i] = [xi, yi] ，并且在 1 <= i < j <= points.length 的前提下， xi < xj 总成立。

请你找出 yi + yj + |xi - xj| 的 最大值，其中 |xi - xj| <= k 且 1 <= i < j <= points.length。

题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。
*/
#include <vector>
#include <deque>
using namespace std;
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //j>i,xj>xi,xi严格递增，也就是说没有重复的xi
        //要满足|xj-xi|<=k时，遍历右端点，左端点是不回退的
        //yi可能为负数，因此无法直接使用双指针，那么我们就考虑单调队列
        //遍历数组每一个下标索引作为右端点
        //先将式子变形 yi + yj + |xi - xj| = yj + xj - xi + yi
        //维护yi-x1的单调队列
        //希望找到在满足xj-xi>=k的窗口内的yi-xi最大值,因为我们遍历右端点
        //对于每个右端点xj,yj是被固定的，需要找的是这个窗口内的yi-xi最大值，
        //因为这个窗口中的所有元素都满足条件|xj-xi|<=k
        int n = points.size();
        deque<int> dq;
        long long ans = INT_MIN;
        int l = 0, r = 0;
        for (; r < n; r++)
        {
            //如果队首不满足，就弹出
            while (!dq.empty() && points[r][0] - points[dq.front()][0] > k)
            {
                dq.pop_front();
            }
            //结算答案
            if (!dq.empty())
            {
                ans = max(ans, (long long)points[dq.front()][1] - points[dq.front()][0] + points[r][0] + points[r][1]);
            }           
            //维护yi-xi的单调队列，因为每一个右端点都必须入队
            while (!dq.empty() && points[r][1]-points[r][0] >= points[dq.back()][1]-points[dq.back()][0])
            {
                dq.pop_back();
            }
            dq.push_back(r);
                  
        }
        /*
        最后一个点 r = n-1 入队后，它可能作为 i 与未来的 j 配对，但已经没有未来了，所以确实"漏掉"了。
        但是，这其实是正确的！因为题目要求 i < j，所以：
        每个点 r 在作为 j 时，与队列中已有的点 i（即索引小于 r 的点）配对
        每个点 r 在作为 i 时，与未来的点 j（即索引大于 r 的点）配对
        对于最后一个点 r = n-1：
        它作为 j：与队列中已有的所有点配对 ✓（在第2步计算答案）
        它作为 i：没有未来的 j 了，所以不需要考虑 ✓
        */
        return ans;
    }
};
//另外本题也可以使用优先队列priority_queue来维护最大的yi-xi，本质上与单调队列的想法相同，借助堆更好管理
//但是时间复杂度变为O(nlogn)
//做题时，无论题目变成什么样，请记住一个核心原则：及时移除(头部或尾部的)无用数据，保证队列/栈的有序性。