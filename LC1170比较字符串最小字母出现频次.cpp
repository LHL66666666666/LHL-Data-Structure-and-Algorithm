/*
定义一个函数 f(s)，统计 s  中（按字典序比较）最小字母的出现频次 ，
其中 s 是一个非空字符串。

例如，若 s = "dcce"，那么 f(s) = 2，因为字典序最小字母是 "c"，它出现了 2 次。

现在，给你两个字符串数组待查表 queries 和词汇表 words 。
对于每次查询 queries[i] ，需统计 words 中满足 f(queries[i]) < f(W) 的 词的数目 ，W 表示词汇表 words 中的每个词。

请你返回一个整数数组 answer 作为答案，其中每个 answer[i] 是第 i 次查询的结果。
*/
/*
1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10    ！！！！！！
queries[i][j]、words[i][j] 都由小写英文字母组成
*/
class Solution {
public:
    int binSearch(int a[], int target,int size)
    {
        //目标是查找小于等于target的最大元素的下标
        int n = size;
        int l = 0, r = n - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (a[mid] <= target)
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return ans;
    }
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> ret;
        int n = queries.size();
        int m = words.size();
        //word可以进行预处理，同时必须也要把queries预处理
        //先算出words中每一个次的f(w)的数值,保证每一个word非空
        //开一个哈希表存words中每一个元素的各个字母出现次数，直接按照字典序排列
        //再开一个数组存储每一个f(w)，会不会爆MLE?
        int w1[26] = { 0 };
        int fw[2005] = { 0 };
        int l = 0;
        for (int i = 0; i < m; i++)
        {
            int size = words[i].size();
            for (int p = 0; p < 26; p++)
            {
                w1[p] = 0;
            }
            for (int j = 0; j < size; j++)
            {
                w1[words[i][j]-'a']++;
            }
            for (int k = 0; k < 26; k++)
            {
                if (w1[k] > 0)
                {
                    fw[l] = w1[k];
                    //ret.push_back(w1[k]);
                    l++;
                    break;
                }
            }
        }
        //fw就存储了每一个f(w),后面直接询问即可,最好把f(w)排序，每次查找即可
        //预处理queries
        int w2[26] = { 0 };
        int fs[2005] = { 0 };
        int l2 = 0;
        for (int i = 0; i < n; i++)
        {
            int size2 = queries[i].size();
            //记得把w2置0
            for (int p = 0; p < 26; p++)
            {
                w2[p] = 0;
            }
            for (int j = 0; j < size2; j++)
            {
                w2[queries[i][j] - 'a']++;
            }
            for (int k = 0; k < 26; k++)
            {
                if (w2[k] > 0)
                {
                    fs[l2] = w2[k];
                    //ret.push_back(w2[k]);
                    l2++;
                    break;
                }
            }
        }
        //对f(words)排序
        sort(fw, fw + m);
        for (int i = 0; i < n; i++)
        {
            int tmp = binSearch(fw, fs[i],m);
            if (tmp == -1)
            {
                ret.push_back(m);
            }
            else ret.push_back(m - tmp - 1);
        }
        return ret;
    }
};
//自己的做法：t:O(Mlogm+Nlogn)
//           m:O(m+n)   
//优化，首先实现f(s)的函数
//将words每一个元素计算f,存储在一个哈希表里，关键点是
//由于 queries[i] 和 words[i] 的长度都不超过 10，因此 f(s) 的范围是 [1,10]
//可以使用后缀和处理这个哈希表，然后从后向前遍历查找
//f的实现
/*
题目定义了一个函数 f(s)，用于统计字符串 s 中字典序最小的字母的出现频次。
然后给定两个字符串数组 queries 和 words，要求对于每个 queries[i]，
统计 words 中有多少个字符串 word 满足 f(queries[i]) < f(word)。

在实现函数 f(s) 时，我们首先初始化一个字符变量 ch = ‘z’ 
表示当前遇到的字典序最小的字母，然后再初始化一个整数 cnt = 0 
表示该字母的出现次数。接下来依次遍历字符串 s 中的每个字符 c：
如果 c 的字典序小于 ch，则将 ch 更新为 c，并将 cnt 置为 1。
否则如果 c = ch，则令 cnt 加 1。
最后，cnt 即为 s 中字典序最小的字母的出现次数
*/
/*
我们可以提前将所有的 words[i] 在 f(s) 中计算一遍，
由于 queries[i] 和 words[i] 的长度都不超过 10，
因此 f(s) 的范围是 [1,10]。
然后用一个长度固定的整数数组 count 来统计每种 f(words[i]) 的个数
*/
/*
为了加快答案的计算，可以倒序遍历 count，将 count 更新为后缀和数组。
这样一来， queries[i] 对应的答案即为 count[f(queries[i])+1]
*/
class Solution {
public:
    int f(string& s) {
        int cnt = 0;
        char ch = 'z';
        for (auto c : s) {
            if (c < ch) {
                ch = c;
                cnt = 1;
            }
            else if (c == ch) {
                cnt++;
            }
        }
        return cnt;
    }

    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> count(12);
        for (auto& s : words) {
            count[f(s)]++;
        }
        for (int i = 9; i >= 1; i--) {
            count[i] += count[i + 1];
        }
        vector<int> res;
        for (auto& s : queries) {
            res.push_back(count[f(s) + 1]);
        }
        return res;
    }
};
