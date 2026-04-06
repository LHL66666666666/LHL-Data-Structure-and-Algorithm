//小蓝有一个仅包含小写字母的字符串 
//s，同时给定一个正整数
//k。如果一个字符串满足所有字符出现的次数不超过
//k 次，则称为“美丽串”。
//请你找出字符串
//s 中是“美丽串”的最长子字符串的长度。
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
int arr[30];
bool check(int arr[], int k)
{
    for (int i = 0; i < 26; i++)
    {
        if (arr[i] > k)
        {
            return false;
        }
    }
    return true;
}
int getmax(int a, int b) {
    return a > b ? a : b;
}
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    int k;
    scanf("%d", &k);
    //用哈希算法，将小写字符串出现次数存储到一个数组中
    //需要一边维护这个记录出现次数的数组，一边统计并更新最大值
    //使用滑动窗口
    // int i = 0, j = -1, max = 1;
    // while (j < n - 1)
    // {
    //     j++;
    //     arr[s[j] - 'a']++;
    //     while (!check(arr, k))
    //     {
    //         //一旦check函数返回了false,
    //         //证明有的字母出现次数已经超出了k次
    //         //这时候再往回找即可
    //         //此时的滑动窗口是要移动i
    //         max = getmax(max, j - i);
    //         arr[s[i] - 'a']--;
    //         i++;
    //     }
    //     if (j==n-1 && check(arr,k)) {
    //         max=getmax(max,j-i+1);
    //     }
    // }

    //提供一种更好的写法，无需单独判断j=n-1的情况
    int i = 0, j = 0, max = 0;

    while (j < n) {
        // 扩展右边界
        arr[s[j] - 'a']++;

        // 如果窗口不合法，收缩左边界直到合法
        while (!check(arr, k)) {
            arr[s[i] - 'a']--;
            i++;
        }

        // 更新最大长度，每次合法时都需要更新
        max = getmax(max, j - i + 1);
        j++;
    }
    cout << max << endl;
    return 0;
}
//事实上还可以再进行优化，不需要每次遍历26个字母，只需要检查本次加上的字母也没有超过即可
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define int long long

string s;
int k, l, r, ans, p[26];

signed main()
{
    cin >> s >> k;
    l = 0; ans = 0;
    int n = s.size();
    for (r = 0; r < n; r++)
    {
        p[s[r] - 'a']++;
        while (p[s[r] - 'a'] > k)
        {
            p[s[l] - 'a']--;
            l++;
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans << endl;
    return 0;
}