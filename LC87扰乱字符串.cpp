#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool isScramble1(string s1, string s2) {
        int n = s1.length();
        return f1(s1, s2, 0, n - 1, 0, n - 1);
    }
    //递归尝试
    //定义递归函数表示的是字符串s1的[l1,r1]区间与字符串s2的[l2,r2]区间是否是扰乱字符串的关系
    //必须时刻保证r1-l1==r2-l2
    bool f1(string& s1, string& s2, int l1, int r1, int l2, int r2)
    {
        //base case，各自只剩下一个字符，就判断这一个是否相等
        if (l1 == r1)
        {
            return s1[l1] == s2[l2];
        }
        //枚举每一个分割点，讨论交换还是不交换
        //这里交换不需要显式的操作字符串，只需要按照区间对应即可
        //枚举分割点,这里是不进行互换的情况
        for (int i = l1, j = l2; i < r1; i++, j++)
        {
            //如果不交换，前半部分和后半部分都需要对应上，这样就分割为两个子问题
            if (f1(s1, s2, l1, i, l2, j) && f1(s1, s2, i + 1, r1, j + 1, r2))
            {
                return true;
            }
        }
        //枚举分割点,这里是进行互换的情况
        for (int i = l1, j = r2; i < r1; i++, j--)
        {
            //交换，这里注意递归调用的时候每一部分的长度都应该相等，必须对应上
            //而且两个部分都应当是
            if (f1(s1, s2, l1, i, j, r2) && f1(s1, s2, i + 1, r1, l2, j - 1))
            {
                return true;
            }
        }
        return false;
    }
    //记忆化搜索
    //由于两个字符串长度是相等的，我们定义参数是可以只定义s1起始位置l1,s2起始位置l2,长度len
    //这样就避免了四维，用三维即可
    int dp[35][35][35];
    bool isScramble2(string& s1, string& s2) {
        int n = s1.size();
        memset(dp, -1, sizeof(dp));
        return f2(s1, s2, 0, n - 1, 0, n - 1);
    }
    bool f2(string s1, string s2, int l1, int r1, int l2, int r2)
    {
        //base case，各自只剩下一个字符，就判断这一个是否相等
        if (l1 == r1)
        {
            return s1[l1] == s2[l2];
        }
        if (dp[l1][l2][r1 - l1] != -1)
        {
            return dp[l1][l2][r1 - l1];
        }
        //枚举每一个分割点，讨论交换还是不交换
        //这里交换不需要显式的操作字符串，只需要按照区间对应即可
        //枚举分割点,这里是不进行互换的情况
        for (int i = l1, j = l2; i < r1; i++, j++)
        {
            //如果不交换，前半部分和后半部分都需要对应上，这样就分割为两个子问题
            if (f2(s1, s2, l1, i, l2, j) && f2(s1, s2, i + 1, r1, j + 1, r2))
            {
                dp[l1][l2][r1 - l1] = 1;
                return true;
            }
        }
        //枚举分割点,这里是进行互换的情况
        for (int i = l1, j = r2; i < r1; i++, j--)
        {
            //交换，这里注意递归调用的时候每一部分的长度都应该相等，必须对应上
            //而且两个部分都应当是满足扰乱的
            if (f2(s1, s2, l1, i, j, r2) && f2(s1, s2, i + 1, r1, l2, j - 1))
            {
                dp[l1][l2][r1 - l1] = 1;
                return true;
            }
        }
        dp[l1][l2][r1 - l1] = 0;
        return false;
    }
    //严格位置依赖的dp
    bool isScramble(string s1, string s2) {
        memset(dp, 0, sizeof(dp));
        int n = s1.size();
        return f3(s1, s2, n);
    }
    bool f3(string& s1, string& s2, int n)
    {
        //base case
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (s1[i] == s2[j])
                {
                    dp[i][j][1] = 1;
                }
            }
        }
        //位置依赖关系
        //我们假设第三维的参数(字符串的长度)表示层，高层的总是依赖低层的
        //因此我们从低层向高层填
        for (int k = 2; k <= n; k++)
        {
            //k表示length
            //注意这里的l1,l2是有限制的，因为一旦l1+lenth超过n就越界了
            for (int l1 = 0; l1 <= n - k; l1++)
            {
                for (int l2 = 0; l2 <= n - k; l2++)
                {
                    //枚举不交换的情况
                    for (int m = 1; m < k; m++)
                    {
                        if (dp[l1][l2][m] && dp[l1 + m][l2 + m][k - m])
                        {
                            dp[l1][l2][k] = 1;
                            break;
                        }
                    }
                    //枚举交换的情况
                    for (int m = 1; m < k; m++)
                    {
                        if (dp[l1][l2 + k - m][m] && dp[l1 + m][l2][k - m])
                        {
                            dp[l1][l2][k] = 1;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
//时间复杂度O(n^4)因为这个题目本身是四维的枚举，但是我们压缩到三维，
//加上dp过程中的枚举，时间复杂度为O(n^4)