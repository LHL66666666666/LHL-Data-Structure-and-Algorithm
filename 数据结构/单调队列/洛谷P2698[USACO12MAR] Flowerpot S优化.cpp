#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
#include <climits>
using namespace std;
struct node {
	int x, y;
}a[100005];
bool cmp(node p, node q)
{
	return p.x < q.x;
}
int main()
{
	int n, d;
	cin >> n >> d;
	//其实完全没必要对相同的x进行去重并只保留y的最大值和最小值
	//因为我们x对应数值是一样的，那么更新答案的时候得到的len就一样
	//因此不需要去重！！
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	sort(a, a + n, cmp);
	//直接维护两个单调队列，滑动窗口
	deque<int> max_dq, min_dq;
	//max_dq单调减，维护最大值
	//min_dq单调增，维护最小值
	int ans = INT_MAX;
	int l = 0, r = 0;
	for (; r < n; r++)
	{
		//将右端点入队
		while (!max_dq.empty() && a[r].y >= a[max_dq.back()].y)
		{
			max_dq.pop_back();
		}
		max_dq.push_back(r);
		while (!min_dq.empty() && a[r].y <= a[min_dq.back()].y)
		{
			min_dq.pop_back();
		}
		min_dq.push_back(r);
		//如果满足要求，左端点尝试缩小
		while (a[max_dq.front()].y - a[min_dq.front()].y >= d)
		{
			//满足条件，更新答案
			ans = min(ans, a[r].x-a[l].x);
			//更新l
			l++;
			//过期的下标出队列
			if (!max_dq.empty() && max_dq.front() < l)
			{
				max_dq.pop_front();
			}
			if (!min_dq.empty() && min_dq.front() < l)
			{
				min_dq.pop_front();
			}

		}
	}
	if (ans != INT_MAX)
	{
		cout << ans << endl;
	}
	else cout << -1 << endl;
	return 0;
}