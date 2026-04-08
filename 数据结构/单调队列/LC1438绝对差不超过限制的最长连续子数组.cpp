#include <vector>
#include <deque>
#include <queue>
using namespace std;
/*
子数组越长，子数组的最大值越大，最小值越小，
最大值与最小值的差值越大，越不能满足题目 ≤limit 的要求。
反之，子数组越短，越满足要求。
子数组范围（也就是窗口的长度）与最值之间存在单调性关系
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        //思路是维护两个单调队列，一个存储最小值，一个存储最大值
        //注意都是正整数
        //关键点：当我们维护一个滑动窗口时，
        //如果窗口向右扩展，那么这一段的最大值一定不会变小，最小值一定不会变大
        //也就是说，最大值更大，最小值更小（或者维持不变）
        //如果窗口从左收缩，那么这一段的最大值一定不会变大，最小值一定不会变小
        //也就是说，最大值更小，最小值更大（或者维持不变）
        //由此我们得出如何维护这个窗口
        //如果当前窗口不满足要求，那么证明绝对值差值过大，考虑从左侧收缩
        //反之，如果满足要求，绝对值的差值不那么大，我们可以向右扩展寻找更优答案
        int n = nums.size();
        int ans = 0;
        deque<int> dq1;
        deque<int> dq2;
        //双指针
        int l = 0, r = 0;
        while (l < n && r < n)
        {
            //维护单调减队列dq1
            while (!dq1.empty() && nums[r] >= nums[dq1.back()])
            {
                dq1.pop_back();
            }
            dq1.push_back(r);
            while (!dq1.empty() && dq1.front() < l)
            {
                dq1.pop_front();
            }
            //维护单调增队列dq2
            while (!dq2.empty() && nums[r] <= nums[dq2.back()])
            {
                dq2.pop_back();
            }
            dq2.push_back(r);
            while (!dq2.empty() && dq2.front() < l)
            {
                dq2.pop_front();
            }
            //检查答案
            if (nums[dq1.front()] - nums[dq2.front()] <= limit)
            {
                //达标，向右扩展
                ans = max(ans, r - l + 1);
                r++;
            }
            else l++;   //不达标，l收缩
        }
        return ans;
    }
};

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        //思路是维护两个单调队列，一个存储最小值，一个存储最大值
        //注意都是正整数
        //关键点：当我们维护一个滑动窗口时，
        //如果窗口向右扩展，那么这一段的最大值一定不会变小，最小值一定不会变大
        //也就是说，最大值更大，最小值更小（或者维持不变）
        //如果窗口从左收缩，那么这一段的最大值一定不会变大，最小值一定不会变小
        //也就是说，最大值更小，最小值更大（或者维持不变）
        //由此我们得出如何维护这个窗口
        //如果当前窗口不满足要求，那么证明绝对值差值过大，考虑从左侧收缩
        //反之，如果满足要求，绝对值的差值不那么大，我们可以向右扩展寻找更优答案
        deque<int> min_q, max_q;
        int ans = 0, left = 0;
        //双指针
        //换为更熟悉的枚举一端维护一段，右/左端点不回退的模板
        //枚举右维护左
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];

            // 1. 右边入
            while (!min_q.empty() && x <= nums[min_q.back()]) {
                min_q.pop_back();
            }
            min_q.push_back(i);

            while (!max_q.empty() && x >= nums[max_q.back()]) {
                max_q.pop_back();
            }
            max_q.push_back(i);

            // 2. 左边出
            while (nums[max_q.front()] - nums[min_q.front()] > limit) {
                left++;
                if (min_q.front() < left) { // 队首不在窗口中
                    min_q.pop_front();
                }
                if (max_q.front() < left) { // 队首不在窗口中
                    max_q.pop_front();
                }
            }

            // 3. 更新答案
            ans = max(ans, i - left + 1);
        }
        return ans;
    }
};