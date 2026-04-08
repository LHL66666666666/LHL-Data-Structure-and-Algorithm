#include <vector>
using namespace std;
class Solution {
public:
    int max(int x, int y)
    {
        return x > y ? x : y;
    }
    int findSpecialInteger(vector<int>& arr) {
        //先来个滑动窗口暴力解法
        int n = arr.size();
        int l = 0;
        int cnt = 0, num = 0;
        while (l < n)
        {
            int r = l;
            while ( r < n && arr[l] == arr[r])
            {
                r++;
            }
            if (r - l > cnt)
            {
                cnt = r - l;
                num = arr[l];
            }
            l = r;
            
        }
        return num;
        //虽然我们找的是出现次数最多的数字，但是题目保证只会有一个超过25%的
    }
};

class Solution {
public:
    int binS(vector<int>& arr, int tar)
    {
        int n = arr.size();
        int l = -1, r = n;
        while (l + 1 < r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] >= tar)
            {
                r = mid;
            }
            else l = mid;
        }
        return r;
        //查找大于等于x的最小元素的下标
    }
    int findSpecialInteger(vector<int>& arr) {
        //如果一个数字出现次数超过25%,由于数组有序
        //我们考虑将数组划分为四个部分
        //[0,25%][25%,50%][50%,75%][75%,100%]
        //跟据抽屉原理，这个数字一定最少在两个范围内出现过
        //因为他会跨区间
        //所以要求的数字一定在分割处出现
        //要实现O(logn)，考虑二分
        //我们将每个分隔出的数字作为候选值，分别在有序数组中进行二分查找，
        //比较不同候选值出现个数，选出最大的一个即可
        int cnt = 0, ans = 0;
        int n = arr.size();
        if (n < 4)
        {
            return arr[0];
        }
        //一共选出4个候选值，1/4,1/2,3/4,末尾
        int a = (n + 3) / 4;
        //a计算n/4向上取整
        int x1 = a, x2 = a * 2, x3 = a * 3, x4 = n - 1;
        int l1 = binS(arr, arr[x1]);
        int r1 = binS(arr, arr[x1]+1);
        if (r1 - l1 > cnt) {
            cnt = r1 - l1;
            ans = arr[x1];
        }
        int l2 = binS(arr, arr[x2]);
        int r2 = binS(arr, arr[x2]+1);
        if (r2 - l2 > cnt) {
            cnt = r2 - l2;
            ans = arr[x2];
        }
        int l3 = binS(arr, arr[x3]);
        int r3 = binS(arr, arr[x3]+1);
        if (r3 - l3 > cnt) {
            cnt = r3 - l3;
            ans = arr[x3];
        }
        int l4 = binS(arr, arr[x4]);
        int r4 = binS(arr, arr[x4]+1);
        if (r4 - l4 > cnt) {
            cnt = r4 - l4;
            ans = arr[x4];
        }
        return ans;
    }
};

/*
方法二：二分查找
根据题目要求，满足条件的整数 x 至少在数组 arr 中出现了 span = arr.length / 4 + 1 次，
那么我们可以断定：数组 arr 中的元素 arr[0], arr[span], arr[span * 2], ... 一定包含 x。

我们可以使用反证法证明上述的结论。假设 arr[0], arr[span], arr[span * 2], ... 均不为 x，
由于数组 arr 已经有序，那么 x 只会连续地出现在 arr[0], arr[span], arr[span * 2], ... 
中某两个相邻元素的间隔中，因此其出现的次数最多为 span - 1 次，这与它至少出现 span 次相矛盾。

有了上述的结论，我们就可以依次枚举 arr[0], arr[span], arr[span * 2], ... 中的元素，
并将每个元素在数组 arr 上进行二分查找，得到其在 arr 中出现的位置区间。
如果该区间的长度至少为 span，那么我们就得到了答案。
*/