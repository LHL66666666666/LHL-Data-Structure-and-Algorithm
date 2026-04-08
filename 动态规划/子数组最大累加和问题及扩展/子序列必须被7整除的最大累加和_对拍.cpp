#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;
typedef long long ll;
// 你的动态规划算法
ll dp[200005][7];
ll f_dp(vector<ll>& nums) {
    memset(dp, -1, sizeof(dp));
    int n = nums.size();
    if (n == 1) {
        if (nums[0] % 7 == 0) return nums[0];
        return 0;
    }
    dp[0][nums[0] % 7] = nums[0];
    for (int i = 1; i <= n - 1; i++) {
        int tmp = nums[i] % 7;
        for (int j = 0; j < 7; j++) {
            ll can1 = dp[i - 1][j];
            ll can2 = -1;
            if (dp[i - 1][(j - tmp + 7) % 7] != -1) {
                can2 = dp[i - 1][(j - tmp + 7) % 7] + nums[i];
            }
            dp[i][j] = max(can1, can2);
        }
        dp[i][tmp] = max(dp[i][tmp], nums[i]);
    }
    if (dp[n - 1][0] != -1) return dp[n - 1][0];
    else return 0;
}

// 暴力枚举算法（验证正确性）
ll f_brute(vector<ll>& nums) {
    int n = nums.size();
    ll max_sum = 0;

    // 枚举所有非空子集（1到2^n-1）
    for (int mask = 1; mask < (1 << n); mask++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += nums[i];
            }
        }
        if (sum % 7 == 0 && sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

// 生成随机测试用例
vector<ll> generate_random_test(int n, int max_val) {
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        nums[i] = rand() % (max_val + 1);  // 0到max_val
    }
    return nums;
}

// 对拍主函数
void compare_algorithms(int num_tests = 1000) {
    srand(time(0));

    cout << "开始对拍测试..." << endl;
    cout << "将运行 " << num_tests << " 组测试" << endl;

    int passed = 0;
    int failed = 0;

    for (int test_id = 1; test_id <= num_tests; test_id++) {
        // 生成随机测试用例
        int n = rand() % 10 + 1;  // 数组长度1-10（暴力算法不能太大）
        int max_val = rand() % 100 + 1;  // 数值范围1-100

        vector<ll> nums = generate_random_test(n, max_val);

        // 运行两个算法
        ll result_dp = f_dp(nums);
        ll result_brute = f_brute(nums);

        // 比较结果
        if (result_dp == result_brute) {
            passed++;
            if (test_id <= 5) {  // 只打印前5个成功的测试
                cout << "测试 " << test_id << " ✓" << endl;
                cout << "  数组: ";
                for (ll num : nums) cout << num << " ";
                cout << endl;
                cout << "  DP结果: " << result_dp << ", 暴力结果: " << result_brute << endl;
            }
        }
        else {
            failed++;
            cout << "\n测试 " << test_id << " ✗ 发现错误！" << endl;
            cout << "数组长度: " << n << endl;
            cout << "数组: ";
            for (ll num : nums) cout << num << " ";
            cout << endl;
            cout << "DP算法结果: " << result_dp << endl;
            cout << "暴力算法结果: " << result_brute << endl;
            cout << "差异: " << abs(result_dp - result_brute) << endl;

            // 打印所有能被7整除的子序列
            cout << "\n所有能被7整除的子序列和：" << endl;
            for (int mask = 1; mask < (1 << n); mask++) {
                ll sum = 0;
                vector<ll> subset;
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        sum += nums[i];
                        subset.push_back(nums[i]);
                    }
                }
                if (sum % 7 == 0) {
                    cout << "  和=" << sum << ": ";
                    for (ll num : subset) cout << num << " ";
                    cout << endl;
                }
            }
            cout << "-------------------" << endl;
        }
    }

    cout << "\n对拍结果：" << endl;
    cout << "通过: " << passed << "/" << num_tests << endl;
    cout << "失败: " << failed << "/" << num_tests << endl;

    if (failed == 0) {
        cout << "\n 所有测试通过！你的DP算法正确。" << endl;
    }
    else {
        cout << "\n 发现错误，请检查算法。" << endl;
    }
}

// 特定边界测试
void test_boundary_cases() {
    cout << "\n=== 边界测试 ===" << endl;

    // 测试1: 单个元素能被7整除
    {
        vector<ll> nums = { 7 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试1 {7}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }

    // 测试2: 单个元素不能被7整除
    {
        vector<ll> nums = { 5 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试2 {5}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }

    // 测试3: 所有元素都能被7整除
    {
        vector<ll> nums = { 7, 14, 21 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试3 {7,14,21}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }

    // 测试4: 没有子序列能被7整除
    {
        vector<ll> nums = { 1, 2, 3 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试4 {1,2,3}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }

    // 测试5: 大数测试
    {
        vector<ll> nums = { 100, 200, 300, 400 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试5 {100,200,300,400}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }

    // 测试6: 你的原始测试
    {
        vector<ll> nums = { 1,1,1,1,1,1 };
        ll dp_res = f_dp(nums);
        ll brute_res = f_brute(nums);
        cout << "测试6 {1,1,1,1,1,1}: DP=" << dp_res << ", 暴力=" << brute_res;
        cout << (dp_res == brute_res ? " ✓" : " ✗") << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== 子序列和能被7整除的最大值 - 对拍程序 ===" << endl;

    // 运行边界测试
    test_boundary_cases();

    // 运行随机对拍测试
    compare_algorithms(100);

    return 0;
}