#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) { 
        int n = favorite.size();
        //自己分析出来了
        //首先：一定会成环:因为n个点,n条边,每个点只发出一条边,抽屉原理
        //如果环上的人数大于等于3个，那么这样最多安排环上的人数个
        //如果这个环是两个元素形成的环，
        //那么我们就可以将这个2元素环以及两个元素延伸出来的最长链安排到桌子上
        //且：多个2元素环都可以安排到同一桌子上无冲突
        //下面定义2个元素形成的环叫小环，3个及以上的形成的叫大环
        //问题变成了如何找环的元素数量，答案即为小环以及最长链的元素和、大环元素个数的最大值
        //使用拓扑排序将入度为0的点依次删除，剩下的即为环，环上的元素入度不可能为0
        //favorite本身就表示了图，下标对应的数值就是邻居
        //无需再建图,利用这张已经给定的图统计入度
        vector<int> indegree(n);
        for (int i = 0; i < n; i++)
        {
            indegree[favorite[i]]++;
        }
        //开始拓扑排序，同时传递信息，传递的信息为：链的深度
        //deep[i]表示：在i之前(不包括i)的最长链的长度
        vector<int> deep(n);
        //deep.assign(n, 0);
        queue<int> qe;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                qe.push(i);
            }
        }
        //拓扑排序删掉链上的点
        while (!qe.empty())
        {
            int tmp = qe.front();
            qe.pop();
            //把链的长度推给指向的元素
            int next = favorite[tmp];
            //加一是加上自己的深度，再次注意deep维持的是最长链的长度
            deep[next] = max(deep[next], deep[tmp] + 1);
            //消除影响
            indegree[next]--;
            if (indegree[next] == 0)
            {
                qe.push(next);
            }
        }
        //经过拓扑排序，不在环上的点都被删除了，
        //目前indegree不为0的点都在环上，下面进行统计
        //可能性1：所有小环(中心个数为2)，算上中心点+延伸点，的总个数
        int sum_small_ring = 0;
        //可能性2：所有大环(中心个数>2)，只算中心点的最大值
        int sum_big_ring = 0;
        for (int i = 0; i < n; i++)
        {
            //只关心环
            if (indegree[i] != 0)
            {
                //把自己的入度改为0
                indegree[i] = 0;
                //统计中心点的个数
                int ringsize = 1;
                for (int j = favorite[i]; j != i; j = favorite[j])
                {
                    //别忘了把自己位置入度改成0，防止统计多次(为了找到独立的环)
                    indegree[j] = 0;
                    ringsize++;
                }
                if (ringsize == 2)
                {
                    //如果中心点只有2个，累加到小环和上
                    sum_small_ring = sum_small_ring + 2 + deep[i] + deep[favorite[i]];
                }
                else {
                    sum_big_ring = max(sum_big_ring, ringsize);
                }
            }
        }
        return max(sum_small_ring, sum_big_ring);
        
    }
};