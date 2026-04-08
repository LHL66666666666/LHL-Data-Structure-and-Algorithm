/*
现在有一个打怪类型的游戏，这个游戏是这样的，你有n个技能，每一个技能会有一个伤害，同时若怪物低于一定的血量，则该技能可能造成双倍伤害，每一个技能最多只能释放一次，已知怪物有m点血量，现在想问你最少用几个技能能消灭掉他（血量小于等于0）。

输入描述：
第一行输入一个整数T，代表有T组测试数据。
对于每一组测试数据，一行输入2个整数n和m，代表有n个技能，怪物有m点血量。
接下来n行，每一行输入两个数A和x，代表该技能造成的伤害和怪物血量小于等于x的时候该技能会造成双倍伤害

1 ≤ T ≤ 100
1 ≤ n ≤ 10
0 ≤ m ≤ 10^6
1 ≤ A, x ≤ m

输出描述：
对于每一组数据，输出一行，代表使用的最少技能数量，若无法消灭输出-1。
*/
#include <iostream>
using namespace std;
#include<vector>
struct node {
    //int id;
    int atk;
    int lim;
} a[15];
vector<int> b;
int ans = 1e5 + 5;
void check(vector<int>& b, int m) {
    int cnt = 0;
    for (auto i : b) {
        if (m <= a[i].lim) {
            m -= 2 * a[i].atk;
            ++cnt;
        }
        else {
            m -= a[i].atk;
            ++cnt;
        }
        if (m <= 0) {
            ans = std::min(ans, cnt);
            break;
        }
    }
}
void dfs(vector<int>& b, int idx, int m) {
    if (idx == b.size()) {
        check(b, m);
        return;
    }
    int j = idx;
    for (; j < b.size(); j++) {
        std::swap(b[idx], b[j]);
        dfs(b, idx + 1, m);
        //恢复现场
        std::swap(b[idx], b[j]);
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        ans = 1e5 + 5;
        b.clear();
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].atk >> a[i].lim;
            //a[i].id = i;
            b.emplace_back(i);
        }
        //模拟每种方式
        //生成全排列
        dfs(b, 0, m);
        if (ans < 1e5 + 5) {
            cout << ans << endl;
        }
        else cout << -1 << endl;
    }
    return 0;
}