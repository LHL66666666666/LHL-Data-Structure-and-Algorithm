#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    //要找的两个区间长度一样
    //希望从两边删掉一些0或1，使中间部分相同的情况下，两边各自偏移出一个位置
    //贪心策略，
    //找到字符串中最左的0和最右的0，中间长度加1作为答案候选值
    //找到字符串中最左的1和最右的1，中间长度加1作为答案候选值
    //二者取最大
    //说明：...0.....0...
    //一段包含左侧的0，另一段包含右侧的0
    int l0 = -1, r0 = n;
    int l1 = -1, r1 = n;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            l0 = i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            l1 = i;
            break;
        }
    }
    for (int i = n - 1; i > 0; i--) {
        if (s[i] == '0') {
            r0 = i;
            break;
        }
    }
    for (int i = n - 1; i > 0; i--) {
        if (s[i] == '1') {
            r1 = i;
            break;
        }
    }
    int ans = 0;
    if (l0 == -1) {
        ans = 0;
    }
    else {
        ans = r0 - l0;
    }
    if (l1 != -1) {
        ans = max(ans, r1 - l1);
    }
    cout << ans << '\n';
    return 0;
}
/*
两个0和1数量相等区间的最大长度
给出一个长度为n的01串，现在请你找到两个区间使得这两个区间中，1的个数相等，0的个数也相等
这两个区间可以相交，但是不可以完全重叠，即两个区间的左右端点不可以完全一样
要求找到两个最长的区间，满足以上要求返回区间最大长度
*/
