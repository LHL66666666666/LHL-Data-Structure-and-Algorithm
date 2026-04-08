#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

// 你的修改后代码
ll f_modified(vector<ll>& nums, int k) {
    int n = nums.size();
    if (n == 1) return 0;
    ll ans = -INF;
    deque<int> dq;
    ll sum = 0;

    // 初始化(k+1)的窗口
    for (int i = 0; i <= k; i++) {
        sum += nums[i];
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    ans = max(ans, sum - nums[dq.front()]);

    // 滑动窗口
    for (int i = 1; i <= n - k - 1; i++) {
        int nxt = i + k;
        sum -= nums[i - 1];
        sum += nums[nxt];

        while (!dq.empty() && dq.front() < i) {
            dq.pop_front();
        }

        while (!dq.empty() && nums[dq.back()] > nums[nxt]) {
            dq.pop_back();
        }
        dq.push_back(nxt);

        ans = max(ans, sum - nums[dq.front()]);
    }
    return ans;
}

// 正确的暴力验证（与单调队列解法等价）
ll f_brute_force_correct(vector<ll>& nums, int k) {
    int n = nums.size();
    if (n <= k) return 0;

    ll ans = -INF;

    // 枚举所有长度为k+1的窗口
    for (int start = 0; start <= n - (k + 1); start++) {
        // 计算窗口和
        ll window_sum = 0;
        for (int i = start; i < start + k + 1; i++) {
            window_sum += nums[i];
        }

        // 在窗口内找最小值
        ll min_val = INF;
        for (int i = start; i < start + k + 1; i++) {
            min_val = min(min_val, nums[i]);
        }

        ans = max(ans, window_sum - min_val);
    }

    return ans == -INF ? 0 : ans;
}

int main() {
    // 测试几个例子
    vector<vector<ll>> test_cases = {
        {1, 1, -4, 5, 1, 4},
        {5, 1, 2, 3, 4},
        {100, 1, 1, 1, 200},
        {1, 2, 3, 4, 5},
        {-1, -2, -3, -4, -5}
    };

    vector<int> k_values = { 3, 2, 2, 3, 2 };

    for (size_t i = 0; i < test_cases.size(); i++) {
        if (test_cases[i].size() > k_values[i]) {
            ll ans1 = f_modified(test_cases[i], k_values[i]);
            ll ans2 = f_brute_force_correct(test_cases[i], k_values[i]);

            cout << "测试用例 " << i << ": ";
            if (ans1 == ans2) {
                cout << "通过, ans = " << ans1 << endl;
            }
            else {
                cout << "失败! 修改代码: " << ans1 << ", 暴力验证: " << ans2 << endl;
            }
        }
    }

    return 0;
}