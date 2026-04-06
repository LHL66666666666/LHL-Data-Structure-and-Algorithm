#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

typedef long long ll;

// 修正后的你的解法
ll your_solution(vector<ll>& nums) {
    int n = nums.size();
    if (n == 0) return 0;  // 添加空数组处理
    if (n == 1) return max(0LL, nums[0]);

    // 使用动态数组避免固定大小问题
    vector<ll> pre(n), premax(n);
    vector<ll> suf(n), sufmax(n);
    vector<ll> dp_prefix(n), dp_suffix(n);

    // 前缀和
    pre[0] = nums[0];
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i - 1] + nums[i];
    }

    // 后缀和
    suf[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1] + nums[i];
    }

    // 前缀最大值
    premax[0] = max(0LL, pre[0]);
    for (int i = 1; i < n; i++) {
        premax[i] = max(premax[i - 1], pre[i]);
    }

    // 后缀最大值
    sufmax[n - 1] = max(0LL, suf[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        sufmax[i] = max(sufmax[i + 1], suf[i]);
    }

    // 情况1：不用卷轴
    ll p1 = 0;
    for (int i = 0; i < n; i++) p1 += nums[i];

    // 情况2：用一个卷轴
    dp_prefix[0] = 0LL;
    for (int i = 1; i < n; i++) {
        dp_prefix[i] = max(dp_prefix[i - 1] + nums[i], premax[i]);
    }
    ll p2 = dp_prefix[n - 1];

    // 情况3：用两个卷轴
    dp_suffix[n - 1] = 0LL;
    for (int i = n - 2; i >= 0; i--) {
        dp_suffix[i] = max(dp_suffix[i + 1] + nums[i], sufmax[i]);
    }

    ll p3 = dp_suffix[0];  // 第一个卷轴不用
    for (int i = 1; i < n; i++) {
        p3 = max(p3, dp_prefix[i - 1] + dp_suffix[i]);
    }
    p3 = max(p3, dp_prefix[n - 1]);  // 第二个卷轴不用
    return p3;
    //return max(p1, max(p2, p3));
}

// 修正后的暴力解法
ll brute_force(vector<ll>& nums) {
    int n = nums.size();
    if (n == 0) return 0;  // 空数组和为0

    ll best = LLONG_MIN;

    // 情况0：不使用卷轴
    ll sum = 0;
    for (int i = 0; i < n; i++) sum += nums[i];
    best = max(best, sum);

    // 情况1：使用一个卷轴
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            // 计算刷掉区间[l, r]后的和
            ll current_sum = 0;
            for (int i = 0; i < n; i++) {
                if (i < l || i > r) {  // 不在刷的区间内
                    current_sum += nums[i];
                }
            }
            best = max(best, current_sum);
        }
    }

    // 情况2：使用两个卷轴
    for (int l1 = 0; l1 < n; l1++) {
        for (int r1 = l1; r1 < n; r1++) {
            for (int l2 = 0; l2 < n; l2++) {
                for (int r2 = l2; r2 < n; r2++) {
                    // 计算刷掉两个区间后的和
                    ll current_sum = 0;
                    for (int i = 0; i < n; i++) {
                        // 如果不在任意一个刷的区间内
                        if (!((i >= l1 && i <= r1) || (i >= l2 && i <= r2))) {
                            current_sum += nums[i];
                        }
                    }
                    best = max(best, current_sum);
                }
            }
        }
    }

    return best;
}

// 生成随机测试用例
vector<ll> generate_random_test(int n, int min_val, int max_val) {
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        // 生成[-5, 5]范围的随机数
        nums[i] = (rand() % (max_val - min_val + 1)) + min_val;
    }
    return nums;
}

// 打印数组
void print_vector(const vector<ll>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i != nums.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    srand(time(0));

    cout << "开始对拍测试..." << endl;
    cout << "=================================" << endl;

    // 先测试几个固定的例子
    vector<vector<ll>> fixed_tests = {
        {1, 2, 3, -4, 5},
        {-1, -2, -3, -4},
        {1, 2, 3, 4, 5},
        {0, 0, 0, 0},
        {-1},
        {5},
        {0},
        {3, -2, 3, -2, 3},
        {1, -1, 1, -1, 1},
        {-1, 2, -3, 4, -5, 6},
    };

    cout << "固定测试用例:" << endl;
    for (size_t i = 0; i < fixed_tests.size(); i++) {
        vector<ll> nums = fixed_tests[i];
        ll your_ans = your_solution(nums);
        ll brute_ans = brute_force(nums);

        cout << "测试" << i + 1 << ": ";
        print_vector(nums);
        cout << " -> 你的结果: " << your_ans << ", 暴力结果: " << brute_ans;

        if (your_ans == brute_ans) {
            cout << "right" << endl;
        }
        else {
            cout << "错误！" << endl;
            return 1;
        }
    }

    cout << "\n随机测试:" << endl;
    cout << "=================================" << endl;

    int total_random_tests = 100;
    int passed = 0;

    for (int test_case = 1; test_case <= total_random_tests; test_case++) {
        // 随机生成数组大小1-7（暴力解法不能太大）
        int n = rand() % 50 + 1;
        int min_val = -5;
        int max_val = 5;

        vector<ll> nums = generate_random_test(n, min_val, max_val);

        ll your_ans = your_solution(nums);
        ll brute_ans = brute_force(nums);

        if (your_ans == brute_ans) {
            passed++;
        }
        else {
            cout << "测试" << test_case << "失败!" << endl;
            cout << "数组: ";
            print_vector(nums);
            cout << endl;
            cout << "你的结果: " << your_ans << endl;
            cout << "暴力结果: " << brute_ans << endl;
            return 1;
        }

        // 每10个测试显示进度
        if (test_case % 10 == 0) {
            cout << "已完成 " << test_case << "/" << total_random_tests << " 个测试" << endl;
        }
    }

    cout << "\n=================================" << endl;
    cout << "测试结果: " << passed << "/" << total_random_tests << " 随机测试通过" << endl;
    cout << "所有测试通过！" << endl;

    return 0;
}