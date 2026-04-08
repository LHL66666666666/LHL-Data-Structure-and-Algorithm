/*
给定一个可包含重复数字的序列 nums ，
按任意顺序 返回所有不重复的全排列。
*/
//如果用set的话，时间复杂度不会降低
//但是我们可以进行剪枝
//将数组排序，如果进行交换时遇到与当前元素一样的元素，跳过
//这样就完成了剪枝
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    vector<vector<int>> ans;
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    void dfs(vector<int>& nums, int idx)
    {
        if (idx == nums.size())
        {
            ans.emplace_back(nums);
            return;
        }
        //开一个集合作为标记数组，如果这个数没有被标记过，我们就尝试填入，
        //并将其标记，继续尝试填下一个位置
        //我们需要将没填入这个位置的数字放在这个位置进行尝试
        //并将这个数字记录到集合中，如果集合中没出现过这个数字，证明可以填入
        //因为如果我将一个和该位置的数相同的数字进行交换，相当于重复了
        //这样正好可以保证不会出现重复
        //后面继续尝试其他没被标记过的数
        int j = idx;
        set<int> vis;
        for (; j < nums.size(); j++)
        {
            if (vis.count(nums[j]) == 0)
            {
                vis.insert(nums[j]);
                swap(nums, idx, j);
                dfs(nums, idx + 1);
                swap(nums, idx, j);
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ans;
    }
};

//另一种解法：官方题解的思路，使用标记数组
/*
此题是「46. 全排列」的进阶，序列中包含了重复的数字，要求我们返回不重复的全排列，
那么我们依然可以选择使用搜索回溯的方法来做。

我们将这个问题看作有 n 个排列成一行的空格，我们需要从左往右依次填入题目给定的 n 个数，
每个数只能使用一次。那么很直接的可以想到一种穷举的算法，即从左往右每一个位置都依此尝试填入一个数，
看能不能填完这 n 个空格，在程序中我们可以用「回溯法」来模拟这个过程。

我们定义递归函数 backtrack(idx,perm) 表示当前排列为 perm，
下一个待填入的位置是第 idx 个位置（下标从 0 开始）。那么整个递归函数分为两个情况：

如果 idx=n，说明我们已经填完了 n 个位置，找到了一个可行的解，我们将 perm 放入答案数组中，递归结束。

如果 idx<n，我们要考虑第 idx 个位置填哪个数。根据题目要求我们肯定不能填已经填过的数，
因此很容易想到的一个处理手段是我们定义一个标记数组 vis 来标记已经填过的数，
那么在填第 idx 个数的时候我们遍历题目给定的 n 个数，
如果这个数没有被标记过，我们就尝试填入，并将其标记，
继续尝试填下一个位置，即调用函数 backtrack(idx+1,perm)。
搜索回溯的时候要撤销该个位置填的数以及标记，并继续尝试其他没被标记过的数。
但题目解到这里并没有满足「全排列不重复」 的要求，在上述的递归函数中我们会生成大量重复的排列，
因为对于第 idx 的位置，如果存在重复的数字 i，
我们每次会将重复的数字都重新填上去并继续尝试导致最后答案的重复，因此我们需要处理这个情况。

要解决重复问题，我们只要设定一个规则，保证在填第 idx 个数的时候重复数字只会被填入一次即可。
而在本题解中，我们选择对原数组排序，保证相同的数字都相邻，
然后每次填入的数一定是这个数所在重复数集合中「从左往右第一个未被填过的数字」，即如下的判断条件：
*/
/*
if (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1]) {
    continue;
}
*/
/*
这个判断条件保证了对于重复数的集合，一定是从左往右逐个填入的。

假设我们有 3 个重复数排完序后相邻，那么我们一定保证每次都是拿从左往右第一个未被填过的数字，
即整个数组的状态其实是保证了 [未填入，未填入，未填入] 到 [填入，未填入，未填入]，
再到 [填入，填入，未填入]，最后到 [填入，填入，填入] 的过程的，因此可以达到去重的目标。

*/
class Solution {
    vector<int> vis;

public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            vis[i] = 0;
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};
/*
for循环保证了从数组中从前往后一个一个取值，再用if判断条件。
所以nums[i - 1]一定比nums[i]先被取值和判断。如果nums[i - 1]被取值了，
那vis[i - 1]会被置1，只有当递归再回退到这一层时再将它置0。
每递归一层都是在寻找数组对应于递归深度位置的值，每一层里用for循环来寻找。
所以当vis[i - 1] == 1时，说明nums[i - 1]和nums[i]分别属于两层递归中，
也就是我们要用这两个数分别放在数组的两个位置，这时不需要去重。
但是当vis[i - 1] == 0时，说明nums[i - 1]和nums[i]属于同一层递归中（只是for循环进入下一层循环）
，也就是我们要用这两个数放在数组中的同一个位置上，这就是我们要去重的情况。
*/
/*
同一轮中即使前后数字相同（即重复）也可以加，但是不同轮中不行。以[1,1,2]为例
在第一轮（初始轮）中，先取了第一个1之后，第二个1依然可以取，并不能被continue掉，说明单纯
if (vis[i] || (i > 0 && nums[i] == nums[i - 1])) {
continue;
}是不行的，因为这样的话就会执行continue了。
而什么时候需要continue呢？实际上是第一轮结束后，[1,1,2]已经被加入结果集中之后，
最外层for循环（也就是取可行解第一个元素的for循环）往后运行，走到下标为1的第二个“1”的位置，
我称之为第二轮，在第二轮中先确定可行解第一个元素为“1”之后再调用backtrack进入第二层for循环，
for循环依然从i=0开始走，会发现此时0号位的1是false，那么这个“1”加不加呢？
答案是不能加，因为假设加了之后，第二轮的可行解的[1,1,2]跟第一轮的可行解[1,1,2]是重复的（唯一的区别就是这里面的1和1对应原数组的下标是互换的）。
所以，!vis[i - 1]这个限制条件的作用主要是针对不同轮。

所以，如果两个相同的数字中（为了容易区分，命名为1a 和 1b），前一个（1a）的标记位为false，
说明此时肯定不是在同一轮了（因为每时每刻处于同一轮的一定是标记位同时为true的（好好体会这句话），
况且1a还在前面，如果在同一轮中，1a肯定是true，之所以为false，说明是回溯到1a的父层后， 
先把1a置false，再for遍历到1b），既然不在同一层，那就要注意，不能在1b的轮中再加入1a了
（因为1a的轮中肯定加入过1b了），所以判断1a和1b值相同，同时1a标记位为false，
那就果断continue，那如果1b后面还有1c呢？同样的道理，只需要判断1b的状态是不是false，
如果是false，说明他俩不在同一轮，1b的轮次中肯定加入过1c了，所以1c的轮次中就可以跳过1b
*/