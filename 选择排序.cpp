//例题1
// 75. 颜色分类（待优化）
//给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，
//使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
//我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
//必须在不使用库内置的 sort 函数的情况下解决这个问题。
//下面是利用选择排序实现的一种方法，实际上还可以使用双指针优化
//class Solution {
//public:
//    void sortColors(vector<int>& nums) {
//        for (int i = 0; i < nums.size(); i++)
//        {
//            int min = i;
//            //注意这里最好定义最小值下标而非定义最小值
//            for (int j = i + 1; j < nums.size(); j++)
//            {
//                if (nums[j] < nums[min])
//                {
//                    min = j;
//                }
//            }
//            int temp = nums[i];
//            nums[i] = nums[min];
//            nums[min] = temp;
//
//        }
//    }
//};



//例题2
//4. 寻找两个正序数组的中位数（待优化）
//给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
//请你找出并返回这两个正序数组的 中位数 。
//算法的时间复杂度应该为 O(log(m + n)) 。
//class Solution {
//public:
//    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//        //先用选择排序做，回头再优化
//        for (int i = 0; i < nums2.size(); i++)
//        {
//            nums1.push_back(nums2[i]);
//        }
//        for (int i = 0; i < nums1.size() - 1; i++)
//        {
//            int min = i;
//            for (int j = i + 1; j < nums1.size(); j++)
//            {
//                if (nums1[min] > nums1[j])
//                    min = j;
//            }
//            int temp = nums1[min];
//            nums1[min] = nums1[i];
//            nums1[i] = temp;
//        }
//
//        //排序结束开始算中位数
//        int n = nums1.size();
//        if (n % 2 == 1)
//        {
//            return nums1[n / 2] * 1.0;
//        }
//        else return (nums1[n / 2] + nums1[n / 2 - 1]) / 2.0;
//    }
//};

//例题3
//747. 至少是其他数字两倍的最大数
//给你一个整数数组 nums ，其中总是存在 唯一的 一个最大整数 。
//请你找出数组中的最大元素并检查它是否 至少是数组中每个其他数字的两倍 。
//如果是，则返回 最大元素的下标 ，否则返回 - 1 。
//分析：这题当然可以直接模拟，
//排完序后直接根据下标来找最大元素和次大元素也可以
//因为最大元素唯一
//先排序的做法
//class Solution {
//public:
//    int dominantIndex(vector<int>& nums) {
//        int max = 0;
//        for (int i = 1; i < nums.size(); i++)
//        {
//            if (nums[i] > nums[max])
//            {
//                max = i;
//            }
//        }
//        for (int i = 0; i < nums.size() - 1; i++)
//        {
//            int min = i;
//            for (int j = i + 1; j < nums.size(); j++)
//            {
//                if (nums[min] > nums[j])
//                {
//                    min = j;
//                }
//            }
//            int temp = nums[i];
//            nums[i] = nums[min];
//            nums[min] = temp;
//        }
//        if (nums[nums.size() - 1] >= nums[nums.size() - 2] * 2)
//        {
//            return max;
//        }
//        else return -1;
//    }
//};
//另解：遍历数组分别找到数组的最大值 m1​和次大值 m2​如果 m1≥m2×2 成立，
//则最大值至少是数组其余数字的两倍，此时返回最大值的下标，否则返回 −1。
//为了返回最大值的下标，我们需要在计算最大值的同时记录最大值的下标。
//这样只需要遍历一遍O(n)
//class Solution {
//public:
//    int dominantIndex(vector<int>& nums) {
//        int m1 = -1, m2 = -1;
//        int index = -1;
//		  分别记录最大值、次大值、最大值的下标
//        for (int i = 0; i < nums.size(); i++) {
//            if (nums[i] > m1) {
//                m2 = m1;
//                m1 = nums[i];
//                index = i;
//            }
//            else if (nums[i] > m2) {
//                m2 = nums[i];
//            }
//        }
//        return m1 >= m2 * 2 ? index : -1;
//    }
//};
