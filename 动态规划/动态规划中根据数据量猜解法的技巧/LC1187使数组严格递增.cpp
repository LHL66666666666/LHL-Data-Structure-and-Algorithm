#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
//问题等价于从 a 中找到一个最长严格递增子序列 lis，
//把不在 lis 中的元素替换成 b 中的元素后，a 是严格递增的，
//求不在 lis 中的元素个数的最小值。
//对于最长递增子序列问题（或者一般的动态规划问题），
//通常都可以用「选或不选」和「枚举选哪个」来启发思考
class Solution {
public:
    //解法1：枚举每个位置改或者不改，由于状态较大，使用哈希表来记忆化搜索
    vector<map<int, int>> dp;
    int dfs1(int i, int pre, vector<int>& a, vector<int>& b) {
        if (i < 0) {
            return 0;
        }
        if (auto it = dp[i].find(pre); it != dp[i].end()) {
            return it->second;
        }
        int ans = INF;
        if (a[i] < pre) {
            ans = dfs1(i - 1, a[i], a, b);
        }
        // 二分查找b中小于pre最大数的下标
        //先找>=pre的第一个数字，前一个就是我们需要的
        auto it = lower_bound(b.begin(), b.end(), pre);
        if (it != b.begin()) {
            --it;
            ans = min(ans, dfs1(i - 1, *it, a, b) + 1);
        }
        return dp[i][pre] = ans;
    }
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        dp.resize(n);
        int x = dfs1(n - 1, INF, arr1, arr2);
        if (x < INF) return x;
        return -1;
    }
};
class Solution {
public:
    //解法2，我们已经知道是需要将整个数组拆出一个LIS来，然后替换掉其他的元素，n-len(LIS)即为答案
    //我们不妨考虑哪些元素被没替换掉，也就是说在这个拆出来的LIS里，找这样的元素
    //dp[i]表示以a[i]结尾的LIS的长度(满足修改前提下的)，其中a[i]未被替换
    //a[i]前面一个保留的是a[j],a[j+1]到a[i-1],i-j+1个
    //it查找第一个大于等于a[i]的元素，这个元素不使用，从it-1开始使用，
    //it>=i-j+1,it>=i-j+1
    vector<int> dp;
    int dfs2(int i, vector<int>& a, vector<int>& b) {
        if (i < 0) return -INF;
        if (dp[i] != -1) return dp[i];
        auto it = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        //这里初始化是处理j==-1的情况，也就是要将前面的全部替换为b[i]
        if (it - i < 0) dp[i] = -INF;
        else dp[i] = 0;
        if (i > 0 && a[i - 1] < a[i]) {
            dp[i] = max(dp[i], dfs2(i - 1, a, b));
        }
        for (int j = i - 2; j >= i - it - 1 && j >= 0; j--) {
            if (b[it - (i - j - 1)] > a[j]) {
                dp[i] = max(dp[i], dfs2(j, a, b));
            }
        }
        //表示a[i]没被替换
        return ++dp[i];
    }
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        //末尾加一个INF，方便边界处理,这个INF最终状态下一定被纳入LIS不会改
        arr1.emplace_back(INF);
        int n = arr1.size();
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        dp.assign(n, -1);
        int ans = dfs2(n - 1, arr1, arr2);
        if (ans >= 0) return n - ans;
        return -1;
    }
};
//变形：给定一个数组a
//如果a[i]可以被替换为任意数字，那么至少替换多少个数字使得a严格递增
//由于都是整数，严格递增就是说a[i]比a[i-1]至少大1
//因此严格递增等价于对任意 j<i , a[i]-a[j]>=i-j , a[i]-i>=a[j]-j
//构造b[i]=a[i]-i
//找b的LIS就是要保留的最长长度x
//n-x即为答案