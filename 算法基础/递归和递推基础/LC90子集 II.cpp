/*
给你一个整数数组 nums ，其中可能包含重复元素，
请你返回该数组所有可能的 子集（幂集）。
解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
*/
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    set<vector<int>> ans;
    vector<int> path;
    void f(vector<int>&nums,int idx, vector<int>& path)
    {
        //base case
        if (idx == nums.size())
        {
            ans.insert(path);
            return;
        }
        //idx表示决策到了nums数组的哪一个位置
        //对于每一个元素，我们考虑选择或不选择
        //选择的情况
        path.push_back(nums[idx]);
        f(nums, idx + 1,path);
        //回溯，将新加入的元素要删除
        path.pop_back();    //恢复现场
        //不选择的情况
        f(nums, idx + 1, path);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        f(nums, 0,path);
        for (vector<int> ans0 : ans)
        {
            ret.push_back(ans0);
        }
        return ret;
    }
};
/*
关于“恢复现场”的个人理解：
在递归到某一“叶子节点”（非最后一个叶子）时，答案需要向上返回，
而此时还有其他的子树（与前述节点不在同一子树）未被递归到，又由于path为全局变量。若直接返回，会将本不属于该子树的答案带上去，故需要恢复现场。
恢复现场的方式为：在递归完成后 dfs(i+1); 后，进行与“当前操作”相反的操作，“反当前操作”。
*/
/*
我们也可以用递归来实现子集枚举。

假设我们需要找到一个长度为 n 的序列 a 的所有子序列，
代码框架是这样的：
vector<int> t;
void dfs(int cur, int n) {
    if (cur == n) {
        // 记录答案
        // ...
        return;
    }
    // 考虑选择当前位置
    t.push_back(cur);
    dfs(cur + 1, n, k);
    t.pop_back();
    // 考虑不选择当前位置
    dfs(cur + 1, n, k);
}
上面的代码中，dfs(cur,n) 参数表示当前位置是 cur，原序列总长度为 n。
原序列的每个位置在答案序列中的状态有被选中和不被选中两种，
我们用 t 数组存放已经被选出的数字。在进入 dfs(cur,n) 之前 [0,cur−1] 位置的状态是确定的，
而 [cur,n−1] 内位置的状态是不确定的，dfs(cur,n) 需要确定 cur 位置的状态，
然后求解子问题 dfs(cur+1,n)。对于 cur 位置，我们需要考虑 a[cur] 取或者不取，
如果取，我们需要把 a[cur] 放入一个临时的答案数组中（即上面代码中的 t），
再执行 dfs(cur+1,n)，执行结束后需要对 t 进行回溯；
如果不取，则直接执行 dfs(cur+1,n)。
在整个递归调用的过程中，cur 是从小到大递增的，当 cur 增加到 n 的时候，
记录答案并终止递归。可以看出二进制枚举的时间复杂度是 O(2^n)。

*/

//优化：更容易剪枝的做法
//for循环里面套递归
//我们排序之后对数据分组，相同的数字看作一组，
//对于每一个组讨论这一组中选几个数字
class Solution {
public:
    set<vector<int>> ans;
    vector<int> path;
    void dfs(vector<int> path,vector<int> nums, int idx)
    {
        //base case
        if (idx == nums.size())
        {
            ans.insert(path);
            return;
        }
        //开始滑动窗口找连续的相同元素
        int j = idx + 1;
        while (j < nums.size() && nums[j] == nums[idx])
        {
            j++;
        }
        //这一组选0个元素
        dfs(path, nums, j);
        //此时j指向越界位置
        for (; idx < j; idx++)
        {
            path.push_back(nums[idx]);
            dfs(path, nums, j);
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ret;
        std::sort(nums.begin(), nums.end());
        dfs(path,nums, 0);
        for (auto ans0 : ans)
        {
            ret.push_back(ans0);
        }
        return ret;
    }
};