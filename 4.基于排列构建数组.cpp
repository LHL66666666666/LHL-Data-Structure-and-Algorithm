/*
给你一个 从 0 开始的排列 nums（下标也从 0 开始）。请你构建一个 同样长度 的数组 ans ，
其中，对于每个 i（0 <= i < nums.length），都满足 ans[i] = nums[nums[i]] 。返回构建好的数组 ans 。

从 0 开始的排列 nums 是一个由 0 到 nums.length - 1（0 和 nums.length - 1 也包含在内）的不同整数组成的数组。



示例 1：

输入：nums = [0,2,1,5,3,4]
输出：[0,1,2,4,5,3]
解释：数组 ans 构建如下：
ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
    = [nums[0], nums[2], nums[1], nums[5], nums[3], nums[4]]
    = [0,1,2,4,5,3]
示例 2：

输入：nums = [5,0,1,2,3,4]
输出：[4,5,0,1,2,3]
解释：数组 ans 构建如下：
ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
    = [nums[5], nums[0], nums[1], nums[2], nums[3], nums[4]]
    = [4,5,0,1,2,3]


提示：

1 <= nums.length <= 1000
0 <= nums[i] < nums.length
nums 中的元素 互不相同


进阶：你能在不使用额外空间的情况下解决此问题吗（即 O(1) 内存）？

*/

//普通做法
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++)
        {
            ans.push_back(nums[nums[i]]);
        }
        return ans;
    }
};

//进阶：O(1)做法
/*思路与算法

我们也可以直接对原数组 nums 进行修改。

为了使得构建过程可以完整进行，我们需要让 nums 中的每个元素 nums[i] 能够同时存储「当前值」（即 nums[i]）和「最终值」（即 nums[nums[i]]）。

我们注意到 nums 中元素的取值范围为 [0,999] 闭区间，这意味着 nums 中的每个元素的「当前值」和「最终值」都在 [0,999] 闭区间内。

因此，我们可以使用类似「1000 进制」的思路来表示每个元素的「当前值」和「最终值」。对于每个元素，我们用它除以 1000 的商数表示它的「最终值」，而用余数表示它的「当前值」。

那么，我们首先遍历 nums，计算每个元素的「最终值」，并乘以 1000 加在该元素上。随后，我们再次遍历数组，并将每个元素的值除以 1000 保留其商数。此时 nums 即为构建完成的数组，我们返回该数组作为答案。

细节

在计算 nums[i] 的「最终值」并修改该元素时，我们需要计算修改前 nums[nums[i]] 的值，而 nums 中下标为 nums[i] 的元素可能已被修改，因此我们需要将取下标得到的值对 1000 取模得到「最终值」。

作者：力扣官方题解
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

//对数组进行原地修改，不占用额外的空间
//由于n范围是0到999考虑把最终值存储在高位上
//低位上始终是初始值

class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        int n = nums.size();
        // 第一次遍历编码最终值
        for (int i = 0; i < n; ++i) {
            nums[i] += 1000 * (nums[nums[i]] % 1000);
        }
        // 第二次遍历修改为最终值
        for (int i = 0; i < n; ++i) {
            nums[i] /= 1000;
        }
        return nums;
    }
};


//进阶问题解法：数字搬家，O(1) 空间
/*
注意 nums 是一个 0 到 n−1 的排列。元素值的范围和下标的范围，都是 [0,n−1]。所以从 i 开始，不断迭代 i=nums[i]，一定会回到起点 i。

例如 nums=[1,2,0] 的答案为 [2,0,1]：

把 nums[0] 替换成下标为 nums[0]=1 的数，即 nums[1]=2。
把 nums[1] 替换成下标为 nums[1]=2 的数，即 nums[2]=0。
把 nums[2] 替换成下标为 nums[2]=0 的数，即 nums[0]=1。
我把这个过程叫做「数字搬家」：把 nums[1] 搬到 nums[0]，把 nums[2] 搬到 nums[1]，把 nums[0] 搬到 nums[2]。

一组数字搬完家后，还需要继续向后遍历，看看是否还有其他数字也需要搬家。例如 nums=[1,2,0,4,3]，把 1,2,0 这一组搬家后，还有一组 4,3 也需要搬家。结果为 [2,0,1,3,4]。

问题来了，继续向后遍历，怎么知道一个数是否搬过家了？

额外用一个 vis 数组？这不符合题目 O(1) 空间的要求。

由于 nums 中的数都是非负数，我们可以用负数标记搬过家的位置。把 x=nums[i] 加一，再取相反数，就可以保证 x<0。于是，如果遍历到一个负数，可以直接 continue。

根据补码的定义，我们有

−x=(∼x)+1
所以有

−(x+1)=−x−1=(∼x)+1−1= ∼x
所以把 x 用位运算取反即可。

所有数字搬家结束后，把 nums 中的所有数字再取反（复原），即可得到最终答案。

作者：灵茶山艾府
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            if (x < 0) { // 已搬家
                continue;
            }
            int cur = i;
            while (nums[cur] != i) {
                int nxt = nums[cur];
                nums[cur] = ~nums[nxt]; // 把下一个数搬过来，同时做标记（取反）
                cur = nxt;
            }
            nums[cur] = ~x; // 对于这一组的最后一个数，把起点 x=nums[i] 搬过来
        }

        for (int i = 0; i < nums.size(); i++) {
            nums[i] = ~nums[i]; // 复原
        }
        return nums;
    }
};