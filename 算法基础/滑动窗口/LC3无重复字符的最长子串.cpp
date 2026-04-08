//给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
int a[300];
class Solution {
public:
    int max(int x, int y)
    {
        return x > y ? x : y;
    }
    int lengthOfLongestSubstring(string s) {
        //开一个哈希表存储即可,ASCII码作为下标
        memset(a, 0, sizeof(a));
        int n = s.size();
        int l = 0;
        int r = 0;
        int ans = 0;
        for (; l < n; l++)
        {
            r = max(l, r);
            while (r<n && a[s[r]] == 0)
            {
                a[s[r]]++;
                r++;
            }
            ans = max(ans, r - l);
            a[s[l]]--;
        }
        return ans;
    }
};
/*
如果我们依次递增地枚举子串的起始位置，那么子串的结束位置也是递增的！
这里的原因在于，假设我们选择字符串中的第 k 个字符作为起始位置，
并且得到了不包含重复字符的最长子串的结束位置为 rk​
 。那么当我们选择第 k+1 个字符作为起始位置时，首先从 k+1 到 rk
​的字符显然是不重复的，并且由于少了原本的第 k 个字符，我们可以尝试继续增大 rk ，
直到右侧出现了重复字符为止。
这样一来，我们就可以使用「滑动窗口」来解决这个问题了：
*/

//写法2：哈希表记录每个字符上一次出现的位置
int h[300];
class Solution {
public:
    int max(int x, int y)
    {
        return x > y ? x : y;
    }
    int lengthOfLongestSubstring(string s) {
        memset(h, -1, sizeof(h));
        int l = 0, r = 0;
        int ans = 0;
        int n = s.size();
        for (; r < n; r++)
        {
            l = max(l, h[s[r]]+1);
            ans = max(ans, r - l + 1);
            h[s[r]] = r;

        }
        return ans;
    }
};