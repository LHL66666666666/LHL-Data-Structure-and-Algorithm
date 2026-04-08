/*
牛牛和他的朋友们约定了一套接头密匙系统，用于确认彼此身份。密匙由一组数字序列表示，两个密匙被认为是一致的，如果满足以下条件：

密匙 b 的长度不超过密匙 a 的长度。
对于任意 0 <= i < length(b)，有 b[i+1] - b[i] == a[i+1] - a[i]。
现在给定了m个密匙 b 的数组，以及n个密匙 a 的数组。请你返回一个长度为 m 的结果数组 ans，表示每个密匙b都有多少一致的密匙a。
*/
#include <string>
#include <iostream>
#include <vector> 
//using namespace std;
//使用静态数组实现
class Solution {
public:
    //const int N = 3e5 + 5;
    int tree[300005][30];
    int end[300005];
    int pass[300005];
    //cnt记录申请节点的编号
    int cnt;
    //初始化
    void build() {
        cnt = 1;
    }

    //增
    void insert(std::string s) {
        //从头节点开始，首先在头节点+1表示经过了头节点
        //cur表示当前的节点是哪个
        int cur = 1;
        pass[cur]++;
        for (int i = 0; i < s.size(); i++) {
            //path表示下一步的路径
            int path = s[i] - '0' + 9;
            if (s[i] == '#') {
                path = 19;
            }
            if (s[i] == '-') {  // 处理负号
                path = 20;
            }
            if (tree[cur][path] == 0) {
                //分配新的内存编号
                tree[cur][path] = ++cnt;
            }
            //更新当前的节点
            cur = tree[cur][path];
            //经过下一个位置
            pass[cur]++;
        }
        //遍历完之后，将现在在的节点end值+1
        end[cur]++;
    }

    //查询前缀
    int prefix(std::string s) {
        int cur = 1;
        for (int i = 0; i < s.size(); i++) {
            int path = s[i] - '0' + 9;
            if (s[i] == '#') {
                path = 19;
            }
            if (s[i] == '-') {  // 处理负号
                path = 20;
            }
            if (tree[cur][path] == 0) {
                return 0;
            }
            cur = tree[cur][path];
        }
        return pass[cur];
    }

    //清空数组，避免数据污染
    void clear() {
        for (int i = 1; i <= cnt; i++) {
            //因为我们最多用了cnt行
            memset(tree[i], 0, sizeof(tree[i]));
            end[i] = 0;
            pass[i] = 0;
        }
    }
    std::vector<int> countConsistentKeys(std::vector<std::vector<int> >& b,
        std::vector<std::vector<int> >& a) {
        build();
        int n = a.size();
        for (int i = 0; i < n; i++) {
            std::string s;
            int n1 = a[i].size();
            for (int j = 0; j < n1 - 1; j++) {
                std::string s1;
                int diff = a[i][j + 1] - a[i][j];
                //构建差值的字符串
                if (diff >= 10 || diff < 0) {
                    s1.push_back('#');
                    if (diff < 0) {
                        s1.push_back('-');  // 添加负号标记
                        diff = -diff;  // 取绝对值
                    }
                    int tmp = diff;
                    while (tmp) {
                        s1.push_back(tmp % 10 + '0');
                        tmp /= 10;
                    }
                    reverse(s1.begin(), s1.end());
                }
                else {
                    s1.push_back(diff + '0');
                    s1.push_back('#');
                }
                s += s1;
            }
            insert(s);
        }
        //构建完了关于a的前缀树
        //来查询b中每一个的前缀
        std::vector<int> ans;
        int m = b.size();
        for (int i = 0; i < m; i++) {
            std::string s;
            int m1 = b[i].size();
            for (int j = 0; j < m1 - 1; j++) {
                std::string s1;
                int diff = b[i][j + 1] - b[i][j];  // 修正：这里应该是b[i]
                //构建差值的字符串
                if (diff >= 10 || diff < 0) {
                    s1.push_back('#');
                    if (diff < 0) {
                        s1.push_back('-');  // 添加负号标记
                        diff = -diff;  // 取绝对值
                    }
                    int tmp = diff;
                    while (tmp) {
                        s1.push_back(tmp % 10 + '0');
                        tmp /= 10;
                    }
                    reverse(s1.begin(), s1.end());
                }
                else {
                    s1.push_back(diff + '0');
                    s1.push_back('#');
                }
                s += s1;
            }
            ans.emplace_back(prefix(s));
        }
        clear();
        return ans;
    }
};
//突然发现忘记处理负数了
//为了处理负数，扩展一下数组