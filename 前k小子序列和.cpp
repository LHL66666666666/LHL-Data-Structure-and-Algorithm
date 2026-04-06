/*
非负数组前k个最小的子序列累加和
给定一个数组nums，含有n个数字，都是非负数
给定一个正数k，返回所有子序列中累加和最小的前k个累加和
子序列是包含空集的
1 <= n <= 10^5
1 <= nums[i] <= 10^6
1 <= k <= 10^5
注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
时间复杂度O(n*logn) + O(k*logk)，额外空间复杂度O(k)
*/
//这是一类无法使用01背包来解决的问题
//解法是使用堆
//思考：n个数字的数组，子序列有2^n个(包含空序列)
//我们使用枚举每一个子集的方法，
//先对数组排序，组织一个小根堆，
//跟据子集问题中：枚举选哪个的思路：
//也就是我们枚举子集（答案）的第一个数选谁，第二个数选谁，第三个数选谁，依此类推
/*
 // 枚举选哪个：在下标 i 到 n-1 中选一个数，加到 path 末尾
        auto dfs = [&](this auto&& dfs, int i) -> void {
            ans.emplace_back(path); // 不选，把当前子集加入答案
            for (int j = i; j < n; j++) { // 选，枚举选择的数字
                path.push_back(nums[j]);
                dfs(j + 1); // 选 nums[j] 意味着 i 到 j-1 都跳过不选，下一个数从 j+1 开始选
                path.pop_back(); // 恢复现场
            }
*/
//每次弹出堆顶元素时，考虑两种转移：
//1.直接将下一个元素加入序列
//2.将堆顶这个序列的最后一位元素替换为下一个元素
//如何体现了上面的子集枚举？
//弹出堆顶元素相当于：不选，把当前子集加入答案
//直接将下一个元素加入序列相当于：选择当前位置的数字，继续到下一个位置去枚举
//将堆顶这个序列的最后一位元素替换为下一个元素相当于：一步回溯，恢复现场，然后去下个位置枚举
//不过要注意：这两个操作并不处于同一层递归之内
//这种做法本质是把 78. 子集 的「枚举选哪个」写法的 for 循环去掉，把循环变量 j 加到了递归参数中。
//毕竟 for 循环就相当于不断地替换最后一个数，而往下递归则相当于在末尾添加数字。
//在堆中我们维护pair<int,int> 第一维是当前的累加和，第二维是当前序列最后一个位置的数字的下标
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;
auto cmp = [](const pair<ll, int>& a, const pair<ll, int>& b)
    {
        return a.first > b.first;
    };
vector<ll> f(vector<int>& nums, int k)
{
    vector<ll> ret;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    //pair<int,int> 第一维是当前的累加和，第二维是当前序列最后一个位置的数字的下标
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,decltype(cmp)> pq(cmp);
    pq.emplace(nums[0], 0);
    //空集
    ret.emplace_back(0);
    while (ret.size() < k)
    {
        auto tmp = pq.top();
        pq.pop();
        ll sum = tmp.first;
        int id = tmp.second;
        ret.emplace_back(sum);
        if (id + 1 < n)
        {
            pq.emplace(sum + nums[id + 1], id + 1);
            pq.emplace(sum - nums[id] + nums[id + 1], id + 1);
        }
    }
    return ret;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> nums = { 1,1,4,5,1,4 };
    vector<ll> ans = f(nums, 32);
    for (auto i : ans) cout << i << ' ';
    return 0;
}
