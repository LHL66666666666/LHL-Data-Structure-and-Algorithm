/*
给定一个字符串s，长度为n，求s的所有子序列
1.子序列: 指一个字符串删掉部分字符（也可以不删）形成的字符串，可以是不连续的，比如"abcde"的子序列可以有"ace","ad"等等
2.将所有的子序列的结果返回为一个字符串数组
3.字符串里面可能有重复字符，但是返回的子序列不能有重复的子序列，比如"aab"的子序列只有"","a","aa","aab","ab","b"，不能存在2个相同的"ab"
4.返回字符串数组里面的顺序可以不唯一
*/
#include <iostream>
#include <unordered_set>
#include <vector>
#include <cstring>
using namespace std;
//传参：s[i...]，之前的决策路径path，set去重
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * @param s string字符串
     * @return string字符串vector
     */
    unordered_set<string> ret;
    string path;
    void f(string& s, int idx, string& path)
    {
        if (idx == s.size())
        {
            //base case
            ret.insert(path);
            return;
        }
        /*
        //如果不选择
        f(s, idx + 1, path);
        //如果选择
        f(s, idx + 1, path + s[idx]);
        */
        // 选择当前字符
        path.push_back(s[idx]);
        f(s, idx + 1, path);
        path.pop_back();  // 回溯
        // 不选择当前字符
        f(s, idx + 1, path);
    }
    vector<string> generatePermutation(string s) {
        vector<string> ans;
        f(s, 0, path);
        for (string s1 : ret)
        {
            ans.push_back(s1);
        }
        return ans;
    }
};