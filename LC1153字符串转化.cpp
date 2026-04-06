#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    bool f(string& s1, string& s2) {
        if (s1 == s2) return true;
        //注意一个特殊情况，如果s1!=s2且s2同时有26种字符，那么不可行
        //如果s2包含了所有26个字母且s1与s2不同，则必然存在无法解开的映射环
        //因为没有字符能作为中转
        int n = s1.size();
        vector<vector<int>> g2(26);
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            g2[s2[i] - 'a'].emplace_back(i);
            pos[i] = s2[i] - 'a';
        }
        int flag = 1;
        for (int i = 0; i < 26; i++) {
            if (g2[i].empty()) flag = 0;
        }
        if (flag) {
            return false;
        }
        vector<vector<int>> g1(26);
        //一样的字母必须在一组里面
        for (int i = 0; i < n; i++) {
            int id = s1[i] - 'a';
            if (g1[id].empty()) {
                g1[id].emplace_back(pos[i]);
            }
            else {
                int pos1 = pos[i];
                if (g1[id][0] != pos1) {
                    return false;
                }
            }
        }
        return true;
    }
};