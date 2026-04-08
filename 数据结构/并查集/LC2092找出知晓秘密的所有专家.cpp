#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool cmp(const vector<int>& a,const vector<int>& b)
    {
        return a[2] < b[2];
    }
    int father[100005];
    //注意，这里的secret数组，使用时要判断secret[代表元素]为true或false，来反映这一整个集合是否知道秘密
    int secret[100005];
    void build(int n,int f)
    {
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
            secret[i] = 0;
        }
        //第一个被告知的父节点就是0
        father[f] = 0;
        secret[0] = 1;
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
    void unite(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
        {
            //注意这里的合并我们不仅要将父节点合并，还需要将知晓秘密的状态合并
            secret[fy] |= secret[fx];
            father[fx] = fy;
        }
    }
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        int m = meetings.size();
        // 按时间排序
        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b)
            {
                return a[2] < b[2];
            });
        build(n, firstPerson);
        //本题使用了给集合打上标签的技巧
        int l = 0;
        //先使用双指针框出同一时间的范围
        for (; l < m; )
        {
            int r = l;
            while (r + 1 < m && meetings[l][2] == meetings[r + 1][2])
            {
                r++;
            }
            //退出循环时r在满足要求的最后一个位置，不越界
            //检查[l,r]即可,[l,r]目前是同一时刻的
            //先合并
            for (int i = l; i <= r; i++)
            {
                unite(meetings[i][0], meetings[i][1]);
            }
            //再将不满足要求的，也就是不知道秘密的集合打散，变回原状态，也就是说自己的父节点是自己
            for (int i = l; i <= r; i++)
            {
                int e1 = meetings[i][0];
                int e2 = meetings[i][1];
                if (secret[find(e1)] == 0)
                {
                    father[e1] = e1;
                }
                if (secret[find(e2)] == 0)
                {
                    father[e2] = e2;
                }
            }
            l = r + 1;
        }
        //最后统计知晓秘密的人数，也就是secret[代表节点]为true的人
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (secret[find(i)])
            {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};