#include <vector>
#include <stack>
using namespace std;
//这道问题体现了维护一个单调栈来维持答案的可能性
//注意发现题目中存在的单调性
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        //正向遍历，单调栈小压大
        //记录可能作为坡的左端点的位置，只要不满足加入后的单调性的就不入栈
        //因为如果当前元素比栈顶元素大，那么最优解一定出现在栈顶元素作为左边界
        //因此不需要考虑，换句话说，我们正向遍历收集了一个严格单调递减的子列(非连续)
        stack<int> stk;
        for (int i = 0; i < n; i++)
        {
            if (!stk.empty() && nums[i] >= nums[stk.top()])
            {
                continue;
            }
            stk.push(i);
        }
        //反向遍历，枚举每个右端点，结算答案
        //在枚举每一个右端点时，如果他大于或等于栈顶元素，就将栈顶元素弹出，结算答案
        //贪心的思想，从右向左先出现的一定更优
        for (int i = n - 1; i >= 0; i--)
        {
            while (!stk.empty() && nums[i] >= nums[stk.top()])
            {
                ans = max(ans, i - stk.top());
                stk.pop();
            }
        }
        return ans;
    }
};