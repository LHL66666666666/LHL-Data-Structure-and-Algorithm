#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int n;
vector<int> a;
ll merge(int l, int mid, int r) {
    ll cnt = 0;
    int p1 = mid, p2 = r;
    for (; p2 >= mid + 1; p2--) {
        while (p1 >= l && a[p1] > a[p2]) {
            --p1;
        }
        cnt += mid - p1;
    }
    vector<int> tmp;
    int p3 = l, p4 = mid + 1;
    for (; p3 <= mid; p3++) {
        while (p4 <= r && a[p3] > a[p4]) {
            tmp.emplace_back(a[p4]);
            ++p4;
        }
        tmp.emplace_back(a[p3]);
    }
    for (; p4 <= r; p4++) tmp.emplace_back(a[p4]);
    for (int i = l; i <= r; i++) {
        a[i] = tmp[i - l];
    }
    return cnt;
}
ll f(int l, int r) {
    if (l == r) return 0;
    ll ans = 0;
    int mid = l + (r - l) / 2;
    ans += f(l, mid) + f(mid + 1, r) + merge(l, mid, r);
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << f(1, n) << '\n';
    return 0;
}