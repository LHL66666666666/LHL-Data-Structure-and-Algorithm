#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void bubbleSort(vector<int>& arr)
    {
        int n = arr.size();
        for (int i=n-1;i>0;i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i < n; i++)
        {
            nums1[i + m] = nums2[i];
        }
        bubbleSort(nums1);
    }
};
//这是直接使用排序的方法，还可以进一步优化
//使用双指针(分离双指针)
//因为给出的这两个数组本身就是单调不减的
//我们可以使用双指针方法。这一方法将两个数组看作队列，
//每次从两个数组头部取出比较小的数字放到结果中。
//我们为两个数组分别设置一个指针 p1与 p2​
//来作为队列的头部指针。代码实现如下：
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = 0, p2 = 0;
        int sorted[m + n];
        int cur;
        while (p1 < m || p2 < n) {
            if (p1 == m) {
                cur = nums2[p2++];
            }
            else if (p2 == n) {
                cur = nums1[p1++];
            }
            else if (nums1[p1] < nums2[p2]) {
                cur = nums1[p1++];
            }
            else {
                cur = nums2[p2++];
            }
            sorted[p1 + p2 - 1] = cur;
        }
        for (int i = 0; i != m + n; ++i) {
            nums1[i] = sorted[i];
        }
    }
};
//时间复杂度：O(m+n)。
//指针移动单调递增，最多移动 m + n 次，因此时间复杂度为 O(m + n)  
//空间复杂度：O(m + n)。
//需要建立长度为 m + n 的中间数组 sorted



//继续优化：不使用额外内存空间，只在nums1进行修改
//方法三：逆向双指针
//算法
//方法二中，之所以要使用临时变量，是因为如果直接合并到数组 nums1​
//中，nums1​中的元素可能会在取出之前被覆盖。那么如何直接避免覆盖 nums1​
//中的元素呢？观察可知，nums1的后半部分是空的，可以直接覆盖而不会影响结果。
//因此可以指针设置为从后向前遍历，每次取两者之中的较大者放进 nums1​的最后面。
//严格来说，在此遍历过程中的任意一个时刻，
//nums1数组中有 m−p1​−1 个元素被放入 nums1的后半部，
//nums2数组中有 n−p2−1 个元素被放入 nums1​的后半部，
//而在指针 p1​的后面，nums1​数组有 m + n−p1​−1 个位置。
//由于m + n−p1​−1≥m−p1−1 + n−p2​−1等价于p2≥−1
//永远成立，因此 p1​
//后面的位置永远足够容纳被插入的元素，不会产生 p1​
//的元素被覆盖的情况。
//实现代码如下：
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1, p2 = n - 1;
        int tail = m + n - 1;
        int cur;
        while (p1 >= 0 || p2 >= 0) {
            if (p1 == -1) {
                cur = nums2[p2--];
            }
            else if (p2 == -1) {
                cur = nums1[p1--];
            }
            else if (nums1[p1] > nums2[p2]) {
                cur = nums1[p1--];
            }
            else {
                cur = nums2[p2--];
            }
            nums1[tail--] = cur;
        }
    }
};
