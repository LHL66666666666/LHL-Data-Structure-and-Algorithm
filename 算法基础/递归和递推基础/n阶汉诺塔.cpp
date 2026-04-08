//汉诺塔问题
#include <cstdio>
#include <iostream>
#define ll long long
void hanoi(int n, char f, char v, char t)
{
	if (n == 1)
	{
		printf("move %d from %c to %c\n", n, f, t);
		return;
	}
	hanoi(n - 1, f, t, v);
	printf("move %d from %c to %c\n", n, f, t);
	hanoi(n - 1, v, f, t);

}
//int main()
//{
//	char f = 'f', v = 'v', t = 't';
//	hanoi(3, f, v, t);
//	return 0;
//}

//扩展版本
//假设有n根柱子，m个盘子
//我们的策略是将m个盘子中的一部分盘子(k个)先移动到一根柱子上，这样问题规模就变成了n-1根柱子
//状态转移方程：f[n][m]=f[n][k]*2+f[n-1][m-k]
//n-1阶的可以继续递推，直到能解决的3阶为止
ll h[100][100];
int main() {
	int n, m;
	std::cin >> n >> m;
	for (int i = 3; i <= n; i++)
	{
		h[i][1] = 1;
	}
	for (int i = 2; i <= m; i++)
	{
		h[3][i] = 2 * h[3][i - 1] + 1;
	}
	for (int i = 4; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
            h[i][j] = LLONG_MAX;
            for (int k = 1; k < j; k++)
            {
                ll moves = h[i][j] = h[i][k] * 2 + h[i - 1][j - k];
                if (moves < h[i][j])
                {
                    h[i][j] = moves;
                }
			}
		}
	}
	/*for (int i = 1; i <= m; i++)
	{
		std::cout << h[4][i] <<' ';
	}*/
	return 0;

}
#include <climits>
#include <cstring>

using namespace std;

long long h[100][100];

int main() {
    int m, n;  // m个盘子，n根柱子
    std::cin >> m >> n;

    // 初始化数组为最大值
    memset(h, 0x3f, sizeof(h));

    // 边界条件
    // 1. 只有1个盘子时，只需要1次移动
    for (int j = 1; j <= n; j++) {
        h[1][j] = 1;
    }

    // 2. 只有1根柱子时，无法移动多个盘子（除了1个盘子）
    for (int i = 2; i <= m; i++) {
        h[i][1] = LLONG_MAX;  // 不可能
    }

    // 3. 只有2根柱子时，无法移动多个盘子（除了1个盘子）
    for (int i = 2; i <= m; i++) {
        h[i][2] = LLONG_MAX;  // 不可能
    }

    // 4. 经典汉诺塔：3根柱子
    for (int i = 1; i <= m; i++) {
        h[i][3] = (1LL << i) - 1;  // 2^i - 1
    }

    // 动态规划：4根柱子及以上
    for (int i = 4; i <= n; i++) {  // i表示柱子数
        for (int j = 2; j <= m; j++) {  // j表示盘子数
            h[j][i] = LLONG_MAX;

            // 尝试所有可能的分割点
            for (int k = 1; k < j; k++) {
                // Frame-Stewart 算法
                long long moves = 2 * h[k][i] + h[j - k][i - 1];
                if (moves < h[j][i]) {
                    h[j][i] = moves;
                }
            }
        }
    }

    // 输出结果
    std::cout << m << "个盘子，" << n << "根柱子的最小移动次数: " << h[m][n] << std::endl;

    // 可选：打印整个DP表
    std::cout << "\nDP表:" << std::endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (h[i][j] == LLONG_MAX)
                std::cout << "INF ";
            else
                std::cout << h[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}