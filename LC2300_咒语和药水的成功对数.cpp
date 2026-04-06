/*
给你两个正整数数组 spells 和 potions ，长度分别为 n 和 m ，其中 spells[i] 表示第 i 个咒语的能量强度，potions[j] 表示第 j 瓶药水的能量强度。

同时给你一个整数 success 。一个咒语和药水的能量强度 相乘 如果 大于等于 success ，那么它们视为一对 成功 的组合。

请你返回一个长度为 n 的整数数组 pairs，其中 pairs[i] 是能跟第 i 个咒语成功组合的 药水 数目。
*/
class Solution {
public:
    int binSearch(vector<int>& potions, long long success,long long spell)
    {
        int m = potions.size();
        int l = 0, r = m - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if ((long long)potions[mid] * spell >= success)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> pairs;
        //spells要求下标，不能进行排序
        //考虑先将数组potions排序
        sort(potions.begin(), potions.end());
        int n = spells.size(), m = potions.size();
        //考虑用二分查找potions中第一个满足要求的元素
        for (int i = 0; i < n; i++)
        {
            int tmp = binSearch(potions, success, spells[i]);
            if (tmp == -1)
            {
                pairs.push_back(0);
            }
            else pairs.push_back(m - tmp);

            
        }
        return pairs;

    }
};
