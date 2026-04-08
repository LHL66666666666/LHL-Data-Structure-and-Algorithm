/*
给你一个整数数组 nums，
有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。
滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。
*/
#include <vector>
#include <deque>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        deque<int> dq;
        //入队列，维持队列严格大到小的单调性
        //队列里存储的是下标索引
        //先处理最初的k个元素
        for (int i = 0; i < k; i++)
        {
            while (!dq.empty() && nums[i] >= nums[dq.back()])
            {
                //队列尾元素出队列
                dq.pop_back();
            }
            dq.push_back(i);
        }
        for (int i = 0; i <= n - k; i++)
        {
            //维护这个滑动窗口
            //左右边界定义为l,r
            int l = i, r = i + k - 1;
            while (!dq.empty() && nums[r] >= nums[dq.back()])
            {
                dq.pop_back();
            }
            dq.push_back(r);
            while (!dq.empty() && dq.front() < l)
            {
                dq.pop_front();
            }
            //记录答案
            ans.emplace_back(nums[dq.front()]);
        }
        return ans;
    }
};

//数组实现deque的模板
class Solution {
public:
    int dq[100005];
    //两个参数表示双端队列的左右边界
    //h表示头，t表示尾，有效区域是[h,t-1]，也就是说h到t左闭右开
    //通过控制两个参数实现对双端队列的操作
    int h, t;
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        h = 0, t = 0;   //清空
        //先放k-1个进去
        for (int i = 0; i < k - 1; i++)
        {
            while (h < t && nums[i] >= nums[dq[t - 1]])
            {
                --t;
            }
            dq[t++] = i;
        }
        //开始进行滑动窗口
        //这种思路是先形成k-1的窗口，右侧元素入队，结算答案，左侧元素出队
        //然后l++进行下一个窗口
        for (int l = 0, r = k - 1; r < n; l++, r++)
        {
            //右侧元素入队
            while (h < t && nums[r] >= nums[dq[t - 1]])
            {
                --t;
            }
            dq[t++] = r;
            //结算答案
            ans.emplace_back(nums[dq[h]]);
            //左侧元素出队,注意检查队列头的元素是否过期
            if (dq[h] <= l)
            {
                ++h;
            }
        }
        return ans;
    }
};