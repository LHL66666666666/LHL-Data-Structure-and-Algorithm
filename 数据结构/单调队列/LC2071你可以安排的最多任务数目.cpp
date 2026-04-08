/*
给你 n 个任务和 m 个工人。每个任务需要一定的力量值才能完成，需要的力量值保存在下标从 0 开始的整数数组 tasks 中，第 i 个任务需要 tasks[i] 的力量才能完成。每个工人的力量值保存在下标从 0 开始的整数数组 workers 中，第 j 个工人的力量值为 workers[j] 。每个工人只能完成 一个 任务，且力量值需要 大于等于 该任务的力量要求值（即 workers[j] >= tasks[i] ）。

除此以外，你还有 pills 个神奇药丸，可以给 一个工人的力量值 增加 strength 。你可以决定给哪些工人使用药丸，但每个工人 最多 只能使用 一片 药丸。

给你下标从 0 开始的整数数组tasks 和 workers 以及两个整数 pills 和 strength ，请你返回 最多 有多少个任务可以被完成。
*/
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool check(vector<int>& tasks, vector<int>& workers,int tar, int pills, int strength,int n,int m)
    {
        //已经排好序，贪心，选择最小的任务，能力值最大的工人，数量为tar
        vector<int> tsk, wk;
        for (int i = 0; i < tar; i++)
        {
            tsk.emplace_back(tasks[i]);
            wk.emplace_back(workers[m - tar + i]);
        }
        //我们返回值判断能不能够完成tar个任务的指标是药丸是否够用
        //每一个工人贪心选择最优的任务去做，如果没任务可做再吃药丸
        //双端队列维护当前来到的工人能做的任务，如果工人没吃药，选择最小的任务做
        //否则选择当前能做的最大的任务做
        //(感觉优先队列(变成小根堆)也能做)
        //可以,但是如果用堆,还需要开一个pair来存储有没有吃过药，因为一人最多吃一个,就更复杂!!
        //官方题解给出了使用有序集合维护工人能力值的做法，也可以！
        //分离双指针
        int pt = 0, pw = 0;
        //cnt记录使用的药丸数
        int cnt = 0;
        //单调队列
        deque<int> dq;
        for (int i = 0; i < tar; i++)
        {
            //队列存储当前工人能做的工作(不吃药情况下)
            while (pt<tar && tsk[pt] <= wk[i])
            {
                dq.push_back(tsk[pt++]);
            }
            //分情况，如果工人在不吃药的情况下有工作可做，那么做最小的
            if (!dq.empty() && dq.front()<=wk[i])
            {
                //注意这里能做工作的前提是队列有元素且工人能做队首元素
                //为什么要加这个检查：因为队列里面可能是上一个人吃药后加入的
                dq.pop_front();
            }
            else {
                //不得不吃药,吃药之后做能做的最大的
                int tmp = wk[i] + strength;
                ++cnt;
                while (pt<tar && tsk[pt] <= tmp)
                {
                    dq.push_back(tsk[pt++]);
                }
                if (dq.empty())
                {
                    //也就是说吃了药也做不了
                    return false;
                }
                else dq.pop_back();
            }
        }
        return cnt <= pills;

    }
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        //二分答案，因为一个人最多做一项任务，答案范围是[0,min(n,m)]
        int n = tasks.size();
        int m = workers.size();
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int l = 0, r = min(n, m);
        int ans = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(tasks,workers,mid,pills,strength,n,m))
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return ans;
    }
};