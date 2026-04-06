int ht[300];
int hs[300];
class Solution {
public:
    int max(int x, int y)
    {
        return x > y ? x : y;
    }
    bool check()
    {
        for (int i = 0; i < 300; i++)
        {
            if (ht[i] != 0 && hs[i] < ht[i])
            {
                return 0;
            }
        }
        return 1;
    }
    string minWindow(string s, string t) {
        memset(ht, 0, sizeof(ht));
        memset(hs, 0, sizeof(hs));
        //还是需要开一个哈希表存储t中所有字符出现次数
        int m = s.size();
        int n = t.size();
        for (int i = 0; i < n; i++)
        {
            ht[t[i]]++;
        }
        //枚举左，维护右
        int l = 0, r = 0;
        string ans = "";
        int lans = 1e6 + 5;
        //先记录，最后再进行取子串的操作
        int lstart = 0;
        while (l < m)
        {
            r = max(l, r);
            //只能使用笨办法,扩展右侧边界
            while (r<m && !check())
            {
                if (ht[s[r]] == 0)
                {
                    r++;
                }
                else
                {
                    hs[s[r]]++;
                    r++;
                }
            }
            if (r - l < lans && r-l!=0 && check())
            {
                lstart = l;
                lans = r - l;
            }
            //移动左指针 l++ 时，记得减少 hs[s[l]] 的计数!!!
            if (ht[s[l]] != 0)
            {
                hs[s[l]]--;
            }
            l++;
        }
        if (lans < 1e6 + 5)
        {
            ans = s.substr(lstart, lans);
        }
        return ans;
    }
};

//优化：将记录t的字符的哈希表想象为一个负债表，每次记录c的字符时-1，
//维护一个变量，初始值为t的长度，表示目前一共欠债是多少，耶就是说欠t几个字符 
//然后用滑动窗口遍历s，每次记录扩展时是否是有效还债
//缩减窗口时，记录缩减的字符对欠债有无贡献
int d[256];
//负债表
class Solution {
public:
    string minWindow(string s, string t) {
        memset(d, 0, sizeof(d));
        int m = s.size();
        int n = t.size();
        for (int i = 0; i < n; i++)
        {
            d[t[i]]--;
        }
        //维护sum是总负债
        int sum = n;
        int l = 0, r = 0;
        string ans = "";
        int lstart = 0, len = 1e6+5;
        for (; r < m; r++)
        {
            if (d[s[r]] < 0)
            {
                sum--;
            }
            d[s[r]]++;
            if (sum == 0)
            {
                //此时恰好找到右边界
                //收缩左边界
                while (l<m && d[s[l]] > 0)
                {
                    d[s[l]]--;
                    l++;
                }
                //注意！！！每次只有在sum==0才可以更新答案，不然的话会记录sum<0时的答案
                //也就是说更新答案要在sum==0中完成
                if (r - l + 1 < len)
                {
                    len = r - l + 1;
                    lstart = l;
                }
            }
            

        }
        if (len < 1e6 + 5)
        {
            ans = s.substr(lstart, len);
        }
        return ans;
    }
};
//灵茶山艾府的题解的两个方法，对应的就是我这两种解法