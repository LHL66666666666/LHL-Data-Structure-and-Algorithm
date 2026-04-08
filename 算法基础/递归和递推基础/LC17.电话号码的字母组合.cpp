/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。
注意 1 不对应任何字母。
*/
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    string path;
    vector<string> ans;
    void dfs(string path,int idx,string s)
    {
        if (idx == s.size())
        {
            ans.push_back(path);
            return;
        }
        if (s[idx] == '2')
        {
            path.push_back('a');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('b');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('c');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '3')
        {
            path.push_back('d');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('e');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('f');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '4')
        {
            path.push_back('g');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('h');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('i');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '5')
        {
            path.push_back('j');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('k');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('l');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '6')
        {
            path.push_back('m');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('n');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('o');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '7')
        {
            path.push_back('p');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('q');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('r');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('s');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '8')
        {
            path.push_back('t');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('u');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('v');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
        else if (s[idx] == '9')
        {
            path.push_back('w');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('x');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('y');
            dfs(path, idx + 1, s);
            path.pop_back();
            path.push_back('z');
            dfs(path, idx + 1, s);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        dfs(path, 0, digits);
        return ans;

    }
};
//官方题解
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> combinations;
        if (digits.empty()) {
            return combinations;
        }
        unordered_map<char, string> phoneMap{
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        string combination;
        backtrack(combinations, phoneMap, digits, 0, combination);
        return combinations;
    }

    void backtrack(vector<string>& combinations, const unordered_map<char, string>& phoneMap, const string& digits, int index, string& combination) {
        if (index == digits.length()) {
            combinations.push_back(combination);
        }
        else {
            char digit = digits[index];
            const string& letters = phoneMap.at(digit);
            for (const char& letter : letters) {
                combination.push_back(letter);
                backtrack(combinations, phoneMap, digits, index + 1, combination);
                combination.pop_back();
            }
        }
    }
};