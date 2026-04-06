#include <vector>
using namespace std;
typedef long long ll;
class Solution {
public:
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        //算出以每个位置开始的k个连续数字的和
        vector<ll> s(n);
        s[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            s[i] = s[i - 1] + nums[i];
        }
        vector<ll> a(n - k + 1);
        a[0] = s[k - 1];
        for (int i = 1; i <= n - k; i++)
        {
            a[i] = s[i + k - 1] - s[i - 1];
        }
        //跟据处理前后缀的思路，我们考虑枚举分割点
        //pre表示前缀最大值
        vector<ll> pre(n - k + 1);
        //preid表示前缀最大值的下标(相同最大值取较小者)
        vector<int> preid(n - k + 1);
        //suf表示后缀最大值
        vector<ll> suf(n - k + 1);
        //sufid表示后缀最大值的下标(相同最大值取较小者)
        vector<int> sufid(n - k + 1);
        pre[0] = a[0];
        preid[0] = 0;
        suf[n - k] = a[n - k];
        sufid[n - k] = n - k;
        for (int i = 1; i <= n - k; i++)
        {
            if (pre[i - 1] >= a[i])
            {
                pre[i] = pre[i - 1];
                preid[i] = preid[i - 1];
            }
            else {
                pre[i] = a[i];
                preid[i] = i;
            }
        }
        for (int i = n - k - 1; i >= 0; i--)
        {
            if (suf[i + 1] > a[i])
            {
                suf[i] = suf[i + 1];
                sufid[i] = sufid[i + 1];
            }
            else {
                suf[i] = a[i];
                sufid[i] = i;
            }
        }
        //枚举分割点，进行划分
        //总是枚举中间子数组作为划分值
        //注意这里枚举到i位置，将i开头作为中间的子数组进行的划分
        //i前的查询前缀，i+k-1后的查询后缀
        int l, m, r;
        ll sum = -INF;
        for (int i = k; i <= n - k - k; i++)
        {
            ll tmp = a[i] + pre[i - k] + suf[i + k];
            if (tmp > sum)
            {
                sum = tmp;
                l = preid[i - k];
                m = i;
                r = sufid[i + k];
            }
        }
        vector<int> ret = { l,m,r };
        return ret;
    }
};