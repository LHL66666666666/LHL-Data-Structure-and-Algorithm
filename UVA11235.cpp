#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
int n, q;
vector<vector<int>> st;
int query(int l, int r) {
    int d = __lg(r - l + 1);
    return max(st[l][d], st[r - (1LL << d) + 1][d]);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n != 0) {
        cin >> q;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        //这是一个非递减的序列，相同的数都是连在一起的
        //因此我们可以将原序列分段，具体地，相同的数字属于同一段
        //每一段有一个编号，从1开始
        //处理每一个查询(l,r)时，我们找出l,r分别在第几组，
        //假设l在i组，r在j组
        //那么第(i+1,j-1)组的最值就是一个RMQ问题，使用st表处理
        //两个区间端点特判
        //特别地，当i==j或i+1==j时，不需要中间部分
        //pos记录每个数字在第几组
        vector<int> pos(n + 1);
        //cnt记录每组元素数量,下标0弃而不用
        vector<int> cnt(1);
        //rg记录每个组的下标范围[左端点,右端点]
        vector<pair<int, int>> rg(1);
        int id = 1;
        int cur = a[1];
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == cur) {
                pos[i] = id;
                ++sum;
            }
            else {
                cnt.emplace_back(sum);
                rg.emplace_back(i - sum, i - 1);
                sum = 1;
                cur = a[i];
                ++id;
                pos[i] = id;
            }
        }
        cnt.emplace_back(sum);
        rg.emplace_back(n + 1 - sum, n);
        //st表
        st.assign(id + 1, vector<int>(21));
        for (int i = 1; i <= id; i++) {
            st[i][0] = cnt[i];
        }
        for (int d = 1; d <= 20; d++) {
            for (int i = 1; i + (1LL << d) - 1 <= id; i++) {
                st[i][d] = max(st[i][d - 1], st[i + (1LL << (d - 1))][d - 1]);
            }
        }
        while (q--) {
            int L, R;
            cin >> L >> R;
            int l = pos[L], r = pos[R];
            if (l == r) {
                cout << R - L + 1 << '\n';
            }
            else if (l + 1 == r) {
                int can1 = rg[l].second - L + 1, can2 = R - rg[r].first + 1;
                cout << max(can1, can2) << '\n';
            }
            else {
                int can1 = rg[l].second - L + 1, can2 = R - rg[r].first + 1;
                int can3 = query(l + 1, r - 1);
                cout << max({ can1,can2,can3 }) << '\n';
            }
        }
    }
    return 0;
}