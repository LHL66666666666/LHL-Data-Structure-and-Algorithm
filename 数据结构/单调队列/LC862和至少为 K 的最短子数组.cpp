#include <vector>
#include <deque>
using namespace std;
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        //思考：首先考虑子数组的累加和问题，我们考虑构建前缀和
        //由构建前缀信息的思路，我们考虑数组中每一个i结尾的位置，最短向前几个能满足条件
        //由于我们不知道确切要找的数字，无法使用哈希表组织存储
        //我们考虑构建单调队列，严格单调增的单调队列维护了依次成为最小值的可能性
        //我们希望找到j<=i,使得presum_nums[i]-presum_nums[j]>=k
        //因此我们希望presum_numms[j]<=presum_nunms[i]-k
        //也就是j位置的前缀和尽量小，单调队列维护了依次成为最小值的可能性
        //一遍遍历，一边维护单调队列，
        //当队列头部元素达标就弹出，不满足严格递增也弹出(由于单调性)
        int n = nums.size();
        vector<long long> pre(n+1);
        pre[0] = 0;
        //构建前缀和数组
        for (int i = 0; i < n; i++)
        {
            pre[i + 1] = nums[i];
            pre[i + 1] += pre[i];
        }
        //遍历，同时维护单调队列
        deque<int> dq;
        //先加入0位置的0
        dq.push_back(0);
        int ans = INT_MAX;
        for (int r = 1; r <= n; r++)
        {
            //遍历到每一位置,看单调队列头部能否满足条件，满足则弹出并结算答案
            //为什么要先做这件事情：因为我们需要找到i严格小于j的位置，不能先把这个点放进去
            while (!dq.empty() && pre[r] - pre[dq.front()] >= k)
            {
                ans = min(ans, r - dq.front());
                dq.pop_front();
            }
            //加入新的数字，维护单调队列
            while (!dq.empty() && pre[r] <= pre[dq.back()])
            {
                dq.pop_back();
            }
            //入队
            dq.push_back(r);
        }
        if (ans < INT_MAX)
        {
            return ans;
        }
        return -1;
    }
};
//做题时，无论题目变成什么样，请记住一个核心原则：及时移除(头部或尾部的)无用数据，保证队列/栈的有序性。
//我们可以遍历 s，同时用某个合适的数据结构来维护遍历过的 s[i]，并及时移除无用的 s[i]。