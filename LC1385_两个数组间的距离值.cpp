/*
给你两个整数数组 arr1 ， arr2 和一个整数 d ，请你返回两个数组之间的 距离值 。

「距离值」 定义为符合此距离要求的元素数目：对于元素 arr1[i] ，不存在任何元素 arr2[j] 满足 |arr1[i]-arr2[j]| <= d 。
*/
class Solution {
public:
    int binSearch(vector<int>& arr2, int target)
    {
        int n = arr2.size();
        int l = 0, r = n - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr2[mid] > target)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
    int binSearch2(vector<int>& arr2, int target)
    {
        int n = arr2.size();
        int l = 0, r = n - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr2[mid] < target)
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return ans;
    }

    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        //没有下标要求，完全可以都排序,再进行二分查找
        //sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int m = arr1.size();
        int n = arr2.size();
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            //遍历arr1中每一个元素，在arr2中二分查找两个端点
            int tar1 = d + arr1[i], tar2 = arr1[i] - d;
            if (binSearch(arr2, tar1) ==  binSearch2(arr2, tar2)+1 )
            {
                ans++;
            }
            else if (binSearch(arr2, tar1) ==-1 && binSearch2(arr2, tar2)==n-1)
            {
                ans++;
            }
            else if (binSearch(arr2, tar1) ==0 && binSearch2(arr2, tar2)==-1)
            {
                ans++;
            }

        }
        return ans;
    }
};

//更简单的思路
//方法一：排序 + 二分查找
//把 arr2​
//从小到大排序，这样我们可以二分查找。
//遍历 arr1​，设 x = arr1[i]，在 arr2​
//中二分查找 ≥x−d 的最小的数 y。
//如果 y 不存在，或者 y > x + d，那么说明 arr2​
//没有在[x−d, x + d] 中的数，答案加一。
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr2);
        int ans = 0;
        for (int x : arr1) {
            auto it = ranges::lower_bound(arr2, x - d);
            if (it == arr2.end() || *it > x + d) {
                ans++;
            }
        }
        return ans;
    }
};

//方法二：排序 + 双指针
//把 arr1和 arr2​从小到大排序。
//遍历 arr1​，
//设 x = arr1​[i]，同时用另一个指针 j 维护最小的满足 arr2[j]≥x−d 的数的下标。
//
//如果发现 arr2[j] > x + d，那么 arr2​
//没有在[x−d, x + d] 中的数，答案加一。
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        ranges::sort(arr1);
        ranges::sort(arr2);
        int ans = 0, j = 0;
        for (int x : arr1) {
            while (j < arr2.size() && arr2[j] < x - d) {
                //这边可以使用双指针因为arr1，arr2都已经排序好
                //查找arr2[j]<arr1[i]-d
                //一定可以保证arr2[j]<arr1[i+1]-d
                j++;
            }
            if (j == arr2.size() || arr2[j] > x + d) {
                ans++;
            }
        }
        return ans;
    }
};