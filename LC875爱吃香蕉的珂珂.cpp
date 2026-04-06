/*
珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。

珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
*/
//https://leetcode.cn/problems/koko-eating-bananas/description/
class Solution {
public:
    bool check(int v, vector<int>& piles,int h)
    {
        int n = piles.size();
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            res += (piles[i]+v-1) / v;
        }
        if (res <= h)
        {
            return true;
        }
        else return false;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        //确定答案的范围[1,max]，最小且达标的速度范围
        int max = piles[0];
        for (int i = 1; i < n; i++)
        {
            if (piles[i] > max)
            {
                max = piles[i];
            }
        }
        //[1，max]二分
        int l = 1, r = max, ans = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(mid, piles, h))
            {
                //达标，记答案，去左侧二分
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
            //不达标则不记录答案去右侧二分
        }
        return ans;


    }
};