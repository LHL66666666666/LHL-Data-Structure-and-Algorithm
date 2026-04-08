#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

// ================== 你的解法 ==================
ll your_solution(vector<ll>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    ll sum = -INF;
    vector<ll> dp(n);
    dp[0] = nums[0];
    for (int i = 1; i < n; i++) {
        dp[i] = max(nums[i], dp[i - 1] + nums[i]);
    }
    for (int i = 0; i < n; i++) sum = max(sum, dp[i]);

    vector<ll> pre(n);
    pre[0] = dp[0];
    for (int i = 1; i < n; i++) {
        pre[i] = max(pre[i - 1], dp[i]);
    }

    vector<ll> dp2(n);
    dp2[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        dp2[i] = max(nums[i], dp2[i + 1] + nums[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        sum = max(sum, pre[i] + dp2[i + 1]);
    }
    return sum;
}

// ================== 暴力解法 ==================
ll brute_force(vector<ll>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    ll max_sum = -INF;

    // 枚举所有可能的翻转区间 [l, r]
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            // 创建翻转后的数组
            vector<ll> temp = nums;
            reverse(temp.begin() + l, temp.begin() + r + 1);

            // 在翻转后的数组中找最大子数组和
            ll cur = temp[0];
            ll max_cur = temp[0];
            for (int i = 1; i < n; i++) {
                cur = max(temp[i], cur + temp[i]);
                max_cur = max(max_cur, cur);
            }
            max_sum = max(max_sum, max_cur);
        }
    }

    return max_sum;
}

// ================== 更高效的暴力解法（用于较大数据） ==================
ll kadane(vector<ll>& arr) {
    ll cur = arr[0];
    ll max_sum = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        cur = max(arr[i], cur + arr[i]);
        max_sum = max(max_sum, cur);
    }
    return max_sum;
}

ll optimized_brute_force(vector<ll>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    ll max_sum = -INF;

    // 先计算不翻转的情况
    max_sum = max(max_sum, kadane(nums));

    // 枚举所有可能的翻转区间
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            // 原地翻转，避免拷贝整个数组
            reverse(nums.begin() + l, nums.begin() + r + 1);
            ll cur_sum = kadane(nums);
            max_sum = max(max_sum, cur_sum);
            // 翻转回来
            reverse(nums.begin() + l, nums.begin() + r + 1);
        }
    }

    return max_sum;
}

// ================== 随机测试 ==================
void random_test(int test_count, int max_n, int min_val, int max_val) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> size_dist(1, max_n);
    uniform_int_distribution<> value_dist(min_val, max_val);

    int passed = 0;
    int failed = 0;

    for (int test = 1; test <= test_count; test++) {
        int n = size_dist(gen);
        vector<ll> nums(n);

        for (int i = 0; i < n; i++) {
            nums[i] = value_dist(gen);
        }

        ll your_ans = your_solution(nums);
        ll brute_ans;

        if (n <= 8) {  // 小数据用完全暴力
            brute_ans = brute_force(nums);
        }
        else {       // 大数据用优化暴力
            brute_ans = optimized_brute_force(nums);
        }

        if (your_ans == brute_ans) {
            passed++;
            if (test % 100 == 0) {
                cout << "Test " << test << " passed. n=" << n
                    << ", answer=" << your_ans << endl;
            }
        }
        else {
            failed++;
            cout << "\nTest " << test << " FAILED!" << endl;
            cout << "n = " << n << endl;
            cout << "nums: ";
            for (int i = 0; i < min(n, 20); i++) {
                cout << nums[i] << " ";
            }
            if (n > 20) cout << "...";
            cout << endl;
            cout << "Your answer: " << your_ans << endl;
            cout << "Brute answer: " << brute_ans << endl;
            cout << "Difference: " << (your_ans - brute_ans) << endl;

            // 对小数据详细分析
            if (n <= 10) {
                cout << "\nAll possible flip results:" << endl;
                for (int l = 0; l < n; l++) {
                    for (int r = l; r < n; r++) {
                        vector<ll> temp = nums;
                        reverse(temp.begin() + l, temp.begin() + r + 1);
                        ll sum = kadane(temp);
                        cout << "Flip [" << l << "," << r << "]: max sum = " << sum;
                        if (sum == brute_ans) cout << "  <-- OPTIMAL";
                        cout << endl;
                    }
                }
            }
            break; // 遇到错误就停止
        }
    }

    cout << "\n\n========== Test Summary ==========" << endl;
    cout << "Total tests: " << test_count << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "Success rate: " << (passed * 100.0 / test_count) << "%" << endl;
}

// ================== 特定边界测试 ==================
void edge_case_tests() {
    cout << "Running edge case tests..." << endl;

    // 测试1：全正数
    {
        vector<ll> nums = { 1, 2, 3, 4, 5 };
        ll your = your_solution(nums);
        ll brute = brute_force(nums);
        cout << "Test 1 (all positive): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }

    // 测试2：全负数
    {
        vector<ll> nums = { -5, -4, -3, -2, -1 };
        ll your = your_solution(nums);
        ll brute = brute_force(nums);
        cout << "Test 2 (all negative): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }

    // 测试3：只有一个元素
    {
        vector<ll> nums = { 42 };
        ll your = your_solution(nums);
        ll brute = brute_force(nums);
        cout << "Test 3 (single element): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }

    // 测试4：需要翻转的情况
    {
        vector<ll> nums = { 1, 2, -10, 4, 5 };
        ll your = your_solution(nums);
        ll brute = brute_force(nums);
        cout << "Test 4 (need flip): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }

    // 测试5：交替正负
    {
        vector<ll> nums = { 1, -2, 3, -4, 5, -6 };
        ll your = your_solution(nums);
        ll brute = brute_force(nums);
        cout << "Test 5 (alternating): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }

    // 测试6：大数测试
    {
        vector<ll> nums = { 1000000000, -1, 1000000000, -1, 1000000000 };
        ll your = your_solution(nums);
        // 对于大数，我们用优化暴力
        ll brute = optimized_brute_force(nums);
        cout << "Test 6 (large numbers): ";
        if (your == brute) cout << "PASS (" << your << ")" << endl;
        else cout << "FAIL (" << your << " vs " << brute << ")" << endl;
    }
}

// ================== 性能测试 ==================
void performance_test() {
    cout << "\nRunning performance test..." << endl;

    int n = 1000;
    vector<ll> nums(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-1000, 1000);

    for (int i = 0; i < n; i++) {
        nums[i] = dist(gen);
    }

    auto start = chrono::high_resolution_clock::now();
    ll result = your_solution(nums);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "n = " << n << ", result = " << result << endl;
    cout << "Time taken by your solution: " << duration.count() << " microseconds" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "========== 翻转一次最大子数组和对拍程序 ==========\n" << endl;

    // 1. 运行边界测试
    edge_case_tests();

    // 2. 运行随机测试（小规模，便于调试）
    cout << "\n\nRunning random tests (small scale)..." << endl;
    random_test(1000, 8, -10, 10);

    // 3. 运行随机测试（中等规模，验证正确性）
    cout << "\n\nRunning random tests (medium scale)..." << endl;
    random_test(500, 15, -100, 100);

    // 4. 运行随机测试（较大规模，压力测试）
    cout << "\n\nRunning random tests (large scale)..." << endl;
    random_test(100, 50, -1000, 1000);

    // 5. 性能测试
    performance_test();

    return 0;
}