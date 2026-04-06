#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int n, m;
struct node {
    ll k, b, x;
    friend bool operator<(const node& p, const node& q) {
        ll da = 2 * p.k * p.x + p.k + p.b, db = 2 * q.k * q.x + q.k + q.b;
        return da < db;
    }
};
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    priority_queue<node> pq;
    for (int i = 1; i <= m; i++) {
        ll k, b;
        cin >> k >> b;
        pq.emplace(k, b, 0);
    }
    //原价b,如果x个人参加,单价b+k*x,总价x*(b+k*x)=bx+k*x^2
    //其中k<0函数存在最大值，x=-b/2*k时取最大值
    //经典的贪心
    //计算每个项目当前新增加1个人能增加的开支，用大根堆维护，每次取最大者
    //且要取的数字是正数
    ll ans = 0;
    while (n--) {
        auto cur = pq.top();
        pq.pop();
        ll dx = 2 * cur.k * cur.x + cur.k + cur.b;
        if (dx > 0) {
            ans += dx;
            pq.emplace(cur.k, cur.b, cur.x + 1);
        }
        else break;
    }
    cout << ans << '\n';
    return 0;
}
//本题的关键在于每次分配人员时，选择能使‌边际收益‌最大的项目（边际收益指的是当前项目增加一人带来的花费增量）
