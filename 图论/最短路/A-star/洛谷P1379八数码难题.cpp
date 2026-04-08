/*
在 3×3 的棋盘上，摆有八个棋子，每个棋子上标有 1 至 8 的某一数字。
棋盘中留有一个空格，空格用 0 来表示。空格周围的棋子可以移到空格中。
要求解的问题是：给出一种初始布局（初始状态）和目标布局
（为了使题目简单,设目标状态为 123804765），
找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。

输入格式
输入初始状态，一行九个数字，空格用 0 表示。

输出格式
只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数。
保证测试数据中无特殊无法到达目标状态数据。
*/
#include <vector>
#include <queue>
#include <deque>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
//#include<bits/stdc++.h>
using namespace std;
//int dx[4] = { 0,0,1,-1 };
//int dy[4] = { 1,-1,0,0 };
//string tar = "123804765";
//bool check(string s)
//{
//    return s == tar;
//}
//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    string s;
//    cin >> s;
//    vector<vector<int>> a(5, vector<int>(5));
//    int sx, sy;
//    for (int i = 0; i < 9; i++)
//    {
//        if (s[i] == '0') {
//            sx = i / 3;
//            sy = i % 3;
//        }
//    }
//    // cout << sx << ' ' << sy << '\n';
//    //只有0能移动，按照0的位置向四个方向展开,bfs
//    queue<tuple<int, int, string>> qe;
//    set<string> st;
//    qe.emplace(sx, sy, s);
//    st.insert(s);
//    int level = 0;
//    while (!qe.empty())
//    {
//        int n1 = qe.size();
//        for (int k = 0; k < n1; k++)
//        {
//            int x = get<0>(qe.front());
//            int y = get<1>(qe.front());
//            string cur_s = get<2>(qe.front());
//            if (cur_s == tar)
//            {
//                cout << level << '\n';
//                return 0;
//            }
//            qe.pop();
//            //尝试4个方向
//            for (int i = 0; i < 4; i++)
//            {
//                int xn = x + dx[i];
//                int yn = y + dy[i];
//                if (xn >= 0 && xn < 3 && yn >= 0 && yn < 3)
//                {
//                    int lo1 = x * 3 + y;
//                    int lo2 = xn * 3 + yn;
//                    string news = cur_s;
//                    //交换
//                    char tmp = news[lo1];
//                    news[lo1] = news[lo2];
//                    news[lo2] = tmp;
//                    if (st.count(news) == 0)
//                    {
//                        st.insert(news);
//                        qe.emplace(xn, yn, news);
//                    }
//                }
//            }
//        }
//        ++level;
//    }
//    return 0;
//}
////优化:双向广搜：由于初始状态和末状态都是已知
//#include<bits/stdc++.h>
using namespace std;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
string tar = "123804765";
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    if (s == tar) {
        cout << 0 << '\n';
        return 0;
    }
    //只有0能移动，按照0的位置向四个方向展开,bfs
    //双向广搜，准备3个队列small,big,next存储扩展出来的新的状态
    //2个哈希表存储两端搜到的元素
    set<string> vis;
    set<string> small;
    set<string> big;
    set<string> next;
    vis.insert(s);
    vis.insert(tar);
    small.insert(s);
    big.insert(tar);
    int level = 1;
    while (!small.empty())
    {
        //整层弹出
        for (auto& cur : small) {
            int x, y;
            for (int j = 0; j < 10; j++) {
                //找到0(空白可交换)的位置
                if (cur[j] == '0') {
                    x = j / 3;
                    y = j % 3;
                }
            }
            //尝试四个方向
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                string news = cur;
                if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                    //尝试交换
                    int lo1 = x * 3 + y;
                    int lo2 = nx * 3 + ny;
                    char tmp = news[lo1];
                    news[lo1] = news[lo2];
                    news[lo2] = tmp;
                    if (big.count(news) > 0) {
                        //在大的出现过
                        //证明双向搜索相遇，可以返回
                        cout << level << '\n';
                        return 0;
                    }
                    if (vis.count(news) == 0) {
                        vis.insert(news);
                        next.insert(news);
                    }
                }
            }
        }
        //判断哪个作为下一层展开
        int nn = next.size();
        int nb = big.size();
        if (nn >= nb) {
            //big要作为新的small,交换
            set<string> tmp = big;
            big.clear();
            big = next;
            small.clear();
            small = tmp;
        }
        else {
            small.clear();
            small = next;
        }
        next.clear();
        ++level;
    }
    return 0;
}
////双向广搜还可以优化，使用队列的写法,其实也差不多
////优化：A*算法
////估价函数
////h函数可以定义为，不在应该在的位置的棋子个数。(不包含空格)
////容易发现h既是可采纳的，也是一致的。此题可以使用A*算法求解。
////因为不应该在这个位置的棋子数量是理论上最少步骤数，但是实际上由于只有一个自由位置，我们需要更多的步数
//#include<bits/stdc++.h>
//using namespace std;
//int dx[4] = { 0,0,1,-1 };
//int dy[4] = { 1,-1,0,0 };
//string tar = "123804765";
////估价函数
//int h(string& s1, string& s2) {
//    int cnt = 0;
//    for (int i = 0; i < 9; i++) {
//        if (s1[i] != s2[i] && s2[i] != '0') {
//            ++cnt;
//        }
//    }
//    return cnt;
//}
//struct node {
//    string s;
//    int f;
//    int step;
//};
//auto cmp = [](const node& a, const node& b) {
//    return a.f > b.f;
//    };
//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    string s;
//    cin >> s;
//    if (s == tar) {
//        cout << 0 << '\n';
//        return 0;
//    }
//    //优先队列BFS
//    priority_queue<node, vector<node>, decltype(cmp)> pq(cmp);
//    //避免重复出现
//    map<string, int> vis;
//    //源点入队
//    pq.push({ s,h(s,tar),0 });
//    vis[s]++;
//    while (!pq.empty()) {
//        string cur = pq.top().s;
//        int step = pq.top().step;
//        pq.pop();
//        if (cur == tar) {
//            cout << step << '\n';
//            return 0;
//        }
//        int x, y;
//        for (int j = 0; j < 9; j++) {
//            //找到0(空白可交换)的位置
//            if (cur[j] == '0') {
//                x = j / 3;
//                y = j % 3;
//            }
//        }
//        //尝试四个方向
//        for (int i = 0; i < 4; i++) {
//            int nx = x + dx[i];
//            int ny = y + dy[i];
//            string news = cur;
//            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
//                //尝试交换
//                int lo1 = x * 3 + y;
//                int lo2 = nx * 3 + ny;
//                //交换
//                char tmp = news[lo1];
//                news[lo1] = news[lo2];
//                news[lo2] = tmp;
//                if (!vis.count(news)) {
//                    vis[news]++;
//                    //注意这里优先级队列按照估价函数+实际的步数进行排序
//                    pq.push({ news,step + 1 + h(news,tar),step + 1 });
//                }
//            }
//        }
//    }
//    return 0;
//}