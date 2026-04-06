/*
给你一个字符数组 letters，该数组按非递减顺序排序，以及一个字符 target。letters 里至少有两个不同的字符。

返回 letters 中大于 target 的最小的字符。如果不存在这样的字符，则返回 letters 的第一个字符。
*/
class Solution {
public:
    char binSearch(vector<char>& letters, char target)
    {
        int n = letters.size();
        int l = 0, r = n - 1, ans = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (letters[mid] > target)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return letters[ans];
    }
    char nextGreatestLetter(vector<char>& letters, char target) {
        int ans = -1, n = letters.size();
        //目标是查找大于target的最小值
        if (target >= letters[n - 1])
        {
            return letters[0];
        }
        else return binSearch(letters, target);

    }
};