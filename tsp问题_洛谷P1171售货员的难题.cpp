#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n;
int g[25][25];
int dp[(1 << 21)][25];
//dfs(status,cur)表示当前所处的状态(表示经过那些村庄)为status，当前在cur村庄，最短路径
int dfs(int status,int cur)
{
	//base case 全为1的状态，表示所有都走过了
	if (status == ((1 << (n + 1)) - 1))
	{
		//只需要回到1号村子
		return g[cur][1];
	}
	if (dp[status][cur] != -1) return dp[status][cur];
	//枚举下一个去的村子
	//0表示还没去过，1表示已经去过
	int ans = INF;
	for (int i = 2; i <= n; i++)
	{
		if ((status & (1 << i)) == 0)
		{
			ans = min(ans, g[cur][i] + dfs(status | (1 << i), i));
		}
	}
	dp[status][cur] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	//给定一个邻接矩阵
	//g.assign(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> g[i][j];
		}
	}
	//路径要形成一个闭环，我们对于每个j都要选择1个i，但是不能选j=i的
	//不能选对角线上的
	for (int i = 0; i <= (1 << (n + 1)) - 1; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			dp[i][j] = -1;
		}
	}
	//3表示二进制下1100000....，对于0位置，弃而不用，1位置已经走过了,这两位赋值为1
	cout << dfs(3, 1);
	return 0;
}