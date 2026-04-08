#include <iostream>
#include <vector>
#include <map>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
int n;
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    map<int, int> mp;
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = mp[b[i]];
    }
    vector<int> ends;
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(ends.begin(), ends.end(), p[i]);
        if (it == ends.end()) {
            ends.emplace_back(p[i]);
        }
        else {
            auto idx = it - ends.begin();
            ends[idx] = p[i];
        }
    }
    cout << ends.size() << '\n';
    return 0;
}
//本体的关键点是给定的两个序列都是排列，每个数字仅出现1次
//而直接求最长公共子序列会超时
//首先，我们来看这样一个问题：给你一个这样的序列：1,2,3,……,n，再给你一个1—n的排列，求他们的最长公共子序列。
//这个问题很简单，因为第一个序列是一个严格递增的，所以只要在第二个序列中找到一个上升子序列，那么一定会在第一个序列中出现，这个很好证明。
//如果要求最长公共子序列，那求最长上升子序列就行了。
//那回到原来的这个问题，这个问题第一个序列并不是严格递增的。但我们可以给他标号
//给第一个序列的数字重编号，使得新编号递增
//在第二个序列按照新编号构建新的序列，这样只需要在序列二中找最长递增子序列即可
//举例：
//原序列：3 2 1 4 5
//标号：  1 2 3 4 5
//p1
//原序列：3 2 1 4 5
//标号：  1 2 3 4 5
//p2
//原序列：1 2 3 4 5
//标号：  3 2 1 4 5