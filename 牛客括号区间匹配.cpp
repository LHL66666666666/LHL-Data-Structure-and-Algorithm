/*
给定一个由 '[' ，']'，'('，‘)’ 组成的字符串，请问最少插入多少个括号就能使这个字符串的所有括号左右配对。
例如当前串是 "([[])"，那么插入一个']'即可满足。
数据范围：字符串长度满足1<=n<=100
输入描述：
仅一行，输入一个字符串，字符串仅由 '[' ，']' ，'(' ，‘)’ 组成
输出描述：
输出最少插入多少个括号
//注意：本题描述不清，形如([)]的不算正确配对的
//正确的形式只有两种：嵌套或并列
*/
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
vector<vector<int>> dp;
//先尝试递归
int f1(string& s, int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l > r) {
        return 0;
    }
    if (l == r) {
        return 1;
    }
    int ret = INF;
    //这里的可能性分类就是基于嵌套/并列来的
    //考虑嵌套的情况
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) {
        ret = f1(s, l + 1, r - 1);
    }
    //考虑并列的情况，也就是说类似[][][]这样的，将其拆成两部分，枚举划分点，取最小值
    for (int i = l; i <= r - 1; i++)
    {
        int tmp = f1(s, l, i) + f1(s, i + 1, r);
        ret = min(tmp, ret);
    }
    dp[l][r] = ret;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    //发现一点，两种括号实际上是独立的,分开处理
    int n = s.size();
    dp.assign(n + 1, vector<int>(n + 1, -1));
    int ans = f1(s, 0, n - 1);
    cout << ans << '\n';
    return 0;
}