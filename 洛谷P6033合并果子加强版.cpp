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
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> cnt(100005);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int id = 1;
    for (int i = 1; i <= 100005; i++) {
        while (cnt[i]) {
            a[id++] = i;
            --cnt[i];
        }
    }
    ll ans = 0;
    queue<ll> q1, q2;
    for (int i = 1; i <= n; i++) {
        q1.emplace(a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        ll tmp = 0;
        for (int j = 0; j < 2; j++) {
            if (q1.empty()) {
                tmp += q2.front();
                q2.pop();
            }
            else if (q2.empty()) {
                tmp += q1.front();
                q1.pop();
            }
            else {
                if (q1.front() < q2.front()) {
                    tmp += q1.front();
                    q1.pop();
                }
                else {
                    tmp += q2.front();
                    q2.pop();
                }
            }
        }
        ans += tmp;
        q2.emplace(tmp);
    }
    cout << ans << "\n";
    return 0;
}