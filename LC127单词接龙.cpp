/*
字典 wordList 中从单词 beginWord 到 endWord 的 转换序列 是一个按下述规格形成的序列
beginWord -> s1 -> s2 -> ... -> sk：
每一对相邻的单词只差一个字母。
 对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
sk == endWord
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，
返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。
如果不存在这样的转换序列，返回 0 。
*/
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
using namespace std;
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //从两个方向分别进行搜索，哪一侧节点数量少就展开哪一侧，直到双方相遇
        //只需返回路径长度
        //先检查目标单词在不在,建立一张单词表(哈希表)，每次搜到的单词从单词表中删除
        set<string> dic;
        for (auto& wd : wordList)
        {
            dic.insert(wd);
        }
        //要求必须包含结束字符串
        if (dic.count(endWord) == 0)
        {
            return 0;
        }
        //开始双向搜索,需要创建两个哈希表来查询，数量较小的哈希表和数量较大的哈希表
        set<string> small;
        set<string> big;
        big.insert(beginWord);
        small.insert(endWord);
        dic.erase(beginWord);
        dic.erase(endWord);
        //next存储小的哪一侧扩展出来的节点
        set<string> next;
        //level记录BFS层数
        for (int level = 2; small.size() != 0; level++)
        {
            //尝试扩展
            for (auto& wd : small)
            {
                string tmp = wd;
                string old = wd;
                for (int j = 0; j < wd.size(); j++)
                {
                    //每一位尝试
                    for (int k = 'a'; k <= 'z'; ++k)
                    {
                        tmp[j] = k;
                        if (tmp != old)
                        {
                            if (big.count(tmp) != 0)
                            {
                                //搜到了，也就是相遇了
                                return level;
                            }
                            else {
                                //没搜到，存入next,前提是单词表中有
                                if (dic.count(tmp) != 0)
                                {
                                    next.insert(tmp);
                                    dic.erase(tmp);
                                }
                            }
                        }
                    }
                    //尝试完每一位，复原
                    tmp = old;
                }
            }
            //没搜到答案，我们现在有small,big,还有small扩展出来的next
            //判断谁做下一个small
            if (next.size() <= big.size())
            {
                small.clear();
                small = next;
            }
            else {
                set<string> tmp = big;
                big.clear();
                big = next;
                small.clear();
                small = tmp;
            }
            next.clear();
        }
        //如果small.size()==0也就是扩展出来的较小的没有元素，且还没找到路径，那么证明路径不存在
        return 0;
    }
};