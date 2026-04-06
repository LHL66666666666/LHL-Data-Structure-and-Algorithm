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
int n, m;
vector<int> d;
struct node {
    int l, r, id;
    int ans;
};
bool cmp1(const node& a, const node& b) {
    return a.r < b.r;
}
bool cmp2(const node& a, const node& b) {
    return a.id < b.id;
}
int lowbit(int x) {
    return x & -x;
}
void add(vector<int>& tree, int pos, int k) {
    while (pos <= n) {
        tree[pos] += k;
        pos += lowbit(pos);
    }
}
int sum(vector<int>& tree, int pos) {
    int res = 0;
    while (pos > 0) {
        res += tree[pos];
        pos -= lowbit(pos);
    }
    return res;
}
int query(vector<int>& tree, int l, int r) {
    return sum(tree, r) - sum(tree, l - 1);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    d.assign(n + 1, 0);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    //离线处理,因为我们计算的贡献是每个位置到右端点所有的
    //按照右端点升序排序
    cin >> m;
    vector<node> q(m + 1);
    for (int i = 1; i <= m; i++) {
        node j;
        cin >> j.l >> j.r;
        j.id = i;
        q[i] = j;
    }
    sort(q.begin() + 1, q.end(), cmp1);
    //每一个数字的贡献是1，范围是从该位置到上一次这个数字出现的位置之后
    //上次出现的位置
    vector<int> pos(1e6 + 5);
    //维护差分数组
    int idx = 1;
    for (int i = 1; i <= n; i++) {
        add(d, pos[a[i]] + 1, 1);
        add(d, i + 1, -1);
        pos[a[i]] = i;
        while (idx <= m && q[idx].r == i) {
            q[idx].ans = sum(d, q[idx].l);
            ++idx;
        }
    }
    //差分数组对应的原数组是贡献数组，每个位置记录的是自己包括后面所有元素对这个位置的贡献
    sort(q.begin() + 1, q.end(), cmp2);
    for (int i = 1; i <= m; i++) {
        cout << q[i].ans << '\n';
    }
    return 0;
}