#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
int n, m;
vector<vector<int>> st;
int query(int l, int r) {
    int x = __lg(r - l + 1);
    return max(st[l][x], st[r - (1 << x) + 1][x]);
}
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int x = __lg(n);
    st.resize(n + 1, vector<int>(x + 1));
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; j <= x; j++) {
        //st[i][j]表示从位置i开始,长度为2^j的区间内的最大值
        //区间范围是[i,i+2^j-1],因此需要i+(1<<j)-1<=n
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}
/*
可重复贡献问题 是指对于运算 opt 满足 x opt x = x
则对应的区间询问就是一个可重复贡献问题．例如，最大值有max(x,x)=x，gcd 有 gcd(x,x)=x，
所以 RMQ 和区间 GCD 就是一个可重复贡献问题．
同时，区间按位与和区间按位或都可以使用ST表来加速求解
像区间和就不具有这个性质，如果求区间和的时候采用的预处理区间重叠了，则会导致重叠部分被计算两次，这是我们所不愿意看到的．
另外，opt还必须满足结合律才能使用 ST 表求解
*/