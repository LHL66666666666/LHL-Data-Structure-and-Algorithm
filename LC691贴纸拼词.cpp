/*
我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们。如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1 。
注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的，并且 target 被选择为两个随机单词的连接。
*/
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <set>
using namespace std;
class Solution {
public:
    int s1[26];
    int s2[26];
    string f(string& tmp, string& i)
    {
        string ret;
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        for (auto j : tmp)
        {
            s1[j - 'a']++;
        }
        for (auto j : i)
        {
            s2[j - 'a']++;
        }
        for (int i = 0; i < 26; i++)
        {
            s1[i] -= s2[i];
            for (int j = 0; j < s1[i]; j++)
            {
                ret.push_back(i + 'a');
            }
        }
        return ret;
    }
    int minStickers(vector<string>& stickers, string target) {
        //bfs暴搜每一种情况，把每个状态看作一个节点，每个节点选择一个贴纸展开，直到展开到target为空
        //剪枝：可以先对字符串进行排序，由于每一个字符都会被消去，
        //我们找待选择字符串中包含当前节点第一个字符(也就是当前字典序最小的一个)的进行展开，
        //就实现了剪枝
        //如何快速寻找：建图，使用邻接表即可
        vector<vector<string>> g(26);
        //排序预处理+建图
        sort(target.begin(), target.end());
        for (auto& str : stickers)
        {
            sort(str.begin(), str.end());
            //注意这里建图，要把含有的每个字符都建上，还要保证不能重复
            for (int i = 0; i < str.size(); i++)
            {
                //这里每个不同的字符加一次，且只能加一次
                if (i == 0 || (str[i] != str[i - 1]))
                {
                    g[str[i] - 'a'].push_back(str);
                }
            }
        }
        //宽搜
        queue<string> qe;
        //vis检查是否出现过,出现过则不再入队列
        set<string> vis;
        qe.push(target);
        vis.insert(target);
        //深度level
        int level = 1;
        while (!qe.empty())
        {
            //当前层的元素个数
            int size1 = qe.size();
            for (int i = 0; i < size1; i++)
            {
                string tmp = qe.front();
                qe.pop();
                //每次弹出时，展开，只展开能找到其中字典序最小的元素的
                char c = tmp[0];
                for (auto& i : g[c - 'a'])
                {
                    string x=f(tmp, i);
                    //判断结束
                    if (x.size() == 0)
                    {
                        return level;
                    }
                    //如果没出现过才能入队列
                    if (vis.count(x) == 0)
                    {
                        qe.push(x);
                        vis.insert(x);
                    }
                }
            }
            ++level;
        }
        return -1;
    }
};

/*
实际上就是把每个状态看作一个节点，从target开始进行bfs，
每条边代表选择一个sticker进行消除，然后得出下一个节点，
最后一旦碰到空节点，根据bfs的特性，第一次访问到节点的路径最短，
于是可以作为答案直接返回
要注意的是第一次访问最短路径的前提是每条边的权重一样，
比如在这题里面都是1，否则不适用
*/
/*
思路：
从target出发【起始状态】，使用每个贴纸去掉对应个数的字母【状态转移】，
看最终能否出现空字符串【目标状态】。
优化: 优先从左往右去掉当前状态中的字符，减少排列组合情况。
(比如我们删1次stickers[0]同时删1次stickers[1]，就有两个顺序达到同样的效果)
【大白话就是先删a后删b，和先删b后删a一样，我们在乎的是选了ab，而不是排列ab】
*/