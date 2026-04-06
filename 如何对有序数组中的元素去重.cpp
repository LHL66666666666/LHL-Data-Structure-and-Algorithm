/*
在C++中，对有序数组去重，我们可以使用双指针方法。一个指针用于遍历数组，另一个指针用于指向去重后数组的最后一个元素。
由于数组是有序的，相同的元素会连续出现。我们只需要在遍历过程中，跳过重复元素，将不重复的元素按顺序放到数组的前面。
具体步骤：

如果数组为空，则直接返回0。

使用两个指针，一个指针i遍历数组，另一个指针index记录当前非重复元素的最后一个位置。

从第二个元素开始（如果数组长度大于等于2），比较当前元素与前一个元素（即index指向的元素）是否相同。
如果不同，则将index加一，并将当前元素的值赋给index位置。

遍历结束后，index+1即为去重后数组的长度，数组的前index+1个元素就是去重后的元素。

注意：这个方法会修改原数组，将不重复的元素集中在数组的前面。我们返回去重后的数组长度，这样我们就可以通过这个长度来使用去重后的数组。

下面我们写一个函数来实现这个功能。
*/
//方法1：使用STL的unique算法（推荐）
#include <iostream>
#include <vector>
#include <algorithm>

// 使用unique算法去重
std::vector<int> removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return nums;

    // unique将重复元素移到末尾，返回去重后的新结尾
    auto new_end = std::unique(nums.begin(), nums.end());

    // 删除重复元素
    nums.erase(new_end, nums.end());
    return nums;
}
//方法2：双指针法，这个算法使用快慢双指针技巧，
//利用有序数组的特性（重复元素必然相邻），在原地修改数组。
std::vector<int> removeDuplicates(std::vector<int>& nums) {
    // 边界情况处理：空数组直接返回
    if (nums.empty()) return nums;

    // 初始化慢指针，指向第一个不重复元素的位置
    // 初始时，第一个元素肯定是不重复的
    int slow = 0;

    // 快指针从第二个元素开始遍历
    for (int fast = 1; fast < nums.size(); fast++) {
        // 当快指针指向的元素 != 慢指针指向的元素
        // 说明找到了一个新的不重复元素
        if (nums[fast] != nums[slow]) {
            slow++;  // 慢指针向前移动
            nums[slow] = nums[fast];  // 将新元素复制到慢指针位置
        }
        // 如果相等，说明是重复元素，快指针继续前进，慢指针不动
    }

    // 调整数组大小，只保留前 slow+1 个元素
    nums.resize(slow + 1);
    return nums;
}
/*
关键点说明
slow指针的作用：
始终指向当前不重复序列的最后一个位置
标识着"有效"数组的边界！！！

fast指针的作用：
遍历整个数组，寻找新的不重复元素
相当于"侦察兵"，探索前方元素

原地修改：
直接在原数组上操作，不需要额外空间
时间复杂度O(n)，空间复杂度O(1)

有序数组的特性：
重复元素必然相邻，这是算法正确性的前提
如果数组无序，需要先排序才能使用此方法

算法优势
高效：只需遍历一次数组
节省空间：原地修改，不需要额外数组
简洁：代码逻辑清晰，易于理解

这种双指针技巧是处理有序数组去重、合并等问题的经典方法，在很多算法题中都有应用。
*/
//扩展：保留最多k个重复元素
int removeDuplicates(std::vector<int>& nums, int k = 1) {
    // 如果数组长度小于等于k，所有元素都可以保留
    if (nums.size() <= k) return nums.size();

    // 慢指针从第k个位置开始（前k个元素肯定可以保留）
    int slow = k;

    // 快指针从第k个位置开始遍历
    for (int fast = k; fast < nums.size(); fast++) {
        // 关键比较：当前元素是否与慢指针前k个位置的元素不同
        if (nums[fast] != nums[slow - k]) {
            // 如果不同，说明可以保留这个元素
            nums[slow] = nums[fast];
            slow++;
        }
        // 如果相同，说明已经有k个相同元素，跳过这个重复元素
    }

    // 返回新数组的长度
    return slow;
}
//关键逻辑解析
//为什么比较nums[fast]和nums[slow - k]？
//slow - k指向的是当前保留序列中倒数第k个元素
//如果nums[fast] == nums[slow - k]，说明当前元素与倒数第k个元素相同
//这意味着如果保留当前元素，相同元素的数量将超过k个
//因此，只有当它们不同时，我们才保留当前元素