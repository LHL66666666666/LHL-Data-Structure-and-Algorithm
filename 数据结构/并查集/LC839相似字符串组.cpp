/*
如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

给你一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？
*/
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int father[305];
    void build()
    {
        for (int i = 0; i <= 300; i++)
        {
            father[i] = i;
        }
    }
    int find(int x)
    {
        if (x != father[x])
        {
            father[x] = find(father[x]);
        }
        return father[x];
    }
    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
    void Union(int x, int y)
    {
        father[find(x)] = find(y);
    }
    bool similar(string s1, string s2)
    {
        int cnt = 0;
        int n = s1.size();
        for (int i = 0; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                cnt++;
            }
        }
        return cnt <= 2;
    }
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        //就是将相似的字符串合并为一个集合即可
        int ans = n;
        build();
        //满足条件的就合并，每次合并ans--
        //如何判断两个字符串相似，比较两个字符串相同下标不同字符的数量即可，是2就相似
        //如何合并：遍历即可,检查每对的相似性关系
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                //如果不在一个集合，检查相似性，判断是否合并
                if (!isSame(i,j))
                {
                    if (similar(strs[i], strs[j]))
                    {
                        Union(i, j);
                        ans--;
                    }
                }
            }
        }
        return ans;
    }
};
/*
我们把每一个字符串看作点，字符串之间是否相似看作边，那么可以发现本题询问的是给定的图中有多少连通分量。于是可以想到使用并查集维护节点间的连通性。

我们枚举给定序列中的任意一对字符串，检查其是否具有相似性，如果相似，那么我们就将这对字符串相连。

在实际代码中，我们可以首先判断当前这对字符串是否已经连通，如果没有连通，我们再检查它们是否具有相似性，可以优化一定的时间复杂度的常数。
*/