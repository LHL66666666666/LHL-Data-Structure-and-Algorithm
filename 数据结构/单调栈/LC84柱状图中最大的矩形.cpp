/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
*/
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    // struct node {
    //     int l;
    //     int r;
    // }b[100005];
    pair<int, int> b;
    //因为没有必要存储每一个状态，而是结算答案是需要，因此我们直接换成可复用的pair
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        //要找两侧严格比它小的元素,要求大压小
        int n = heights.size();
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && heights[i] <= heights[stk.top()])
            {
                int tmp = stk.top();
                stk.pop();
                //结算答案
                b.second = i;
                if (!stk.empty())
                {
                    b.first = stk.top();
                }
                else b.first = -1;
                ans = max(ans, (long long)(b.second - b.first - 1) * heights[tmp]);
            }
            stk.push(i);
        }
        //不需要修正，如果遇到相同的元素，右边的元素会继承左边元素的左边界，
        //因此答案一定会被最后一个相等的数字修正为正确答案按
        //清算阶段
        while (!stk.empty())
        {
            int tmp = stk.top();
            stk.pop();
            b.second = n;
            if (!stk.empty())
            {
                b.first = stk.top();
            }
            else b.first = -1;
            ans = max(ans, (long long)(b.second - b.first - 1) * heights[tmp]);
        }
        return ans;
    }
};