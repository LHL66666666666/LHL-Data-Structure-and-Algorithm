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
class Solution {
public:
    int n;
    vector<int> tree1, tree2;
    vector<vector<int>> g;
    vector<int> ans;
    vector<int> siz;
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
    void f() {
        for (int i = 0; i < 26; i++) {
            siz[i] = g[i].size();
        }
    }
    int minMovesToMakePalindrome(string s) {
        //贪心：
        //可以证明我们按照顺序遍历字符串，
        //每次固定字符串最左边的字母a不变，找出距离字符串右侧最近的a，
        //把它交换到字符串最右边。这样字符串的头尾字母就相等了
        //把字符串的头尾去掉，就变成了子问题
        //把所有子问题的答案加起来就是最少交换次数
        //注意如果遇到字母出现奇数次，那么一定放在中间一个
        //这样一来，就确定了每个字母最终的位置
        //问题就转化为了将一个1...n的排列p转化为有序的最少操作次数，答案就是排列p的逆序对数量
        n = s.size();
        //首先建立每个数组的下标列表
        //为了加速，使用树状数组来计算每个字符在新字符串中的位置
        //具体地，我们让数组初始为[1,1,....,1]
        //来到i位置，要在新数组所处的位置就是[1,i]前缀和
        //同时我们将和i配对的位置的1置为0
        g.clear();
        g.resize(26);
        siz.resize(26);
        for (int i = 0; i < n; i++) {
            g[s[i] - 'a'].emplace_back(i + 1);
        }
        f();
        tree1.assign(n + 1, 0), tree2.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            add(tree1, i, 1);
        }
        ans.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            if (g[s[i - 1] - 'a'].size() <= siz[s[i - 1] - 'a'] / 2) continue;
            int id = sum(tree1, i);
            //对应位置
            int p1 = g[s[i - 1] - 'a'].back();
            if (i != p1) {
                ans[id] = i;
                ans[n + 1 - id] = p1;
                add(tree1, p1, -1);
                g[s[i - 1] - 'a'].pop_back();
            }
            else if (i == p1) {
                //奇数个元素，放中间
                ans[n / 2 + 1] = i;
                add(tree1, p1, -1);
                g[s[i - 1] - 'a'].pop_back();
            }
        }
        //ans构建好了，找逆序对
        int res = 0;
        for (int i = 1; i <= n; i++) {
            res += query(tree2, ans[i], n);
            add(tree2, ans[i], 1);
        }
        return res;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution s;
    string s1 = "letelt";
    int x = s.minMovesToMakePalindrome(s1);
    cout << x << endl;
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> dis(1,1e6);
    // vector<int> v(20);
    // for (auto &i : v) {
    //     i=dis(gen);
    // }

    return 0;
}