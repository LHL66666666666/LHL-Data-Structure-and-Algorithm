#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef long long ll;

// 你的算法
vector<ll> heap_method(vector<int>& nums, int k) {
    vector<ll> ret;
    int n = nums.size();
    sort(nums.begin(), nums.end());

    auto cmp = [](const pair<ll, int>& a, const pair<ll, int>& b) {
        return a.first > b.first;
        };
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(cmp)> pq(cmp);

    pq.emplace(nums[0], 0);
    ret.emplace_back(0); // 空集

    while (ret.size() < k && !pq.empty()) {
        auto tmp = pq.top();
        pq.pop();
        ll sum = tmp.first;
        int id = tmp.second;
        ret.emplace_back(sum);

        if (id + 1 < n) {
            pq.emplace(sum + nums[id + 1], id + 1);
            pq.emplace(sum - nums[id] + nums[id + 1], id + 1);
        }
    }
    return ret;
}

// 暴力枚举所有子序列的和
vector<ll> brute_force(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> all_sums;

    // 枚举所有子集
    for (int mask = 0; mask < (1 << n); mask++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += nums[i];
            }
        }
        all_sums.push_back(sum);
    }

    // 排序并取前k个（可能有重复）
    sort(all_sums.begin(), all_sums.end());

    if (k > all_sums.size()) {
        k = all_sums.size();
    }

    return vector<ll>(all_sums.begin(), all_sums.begin() + k);
}

// 随机测试
void random_test(int test_num, int max_n, int max_val, int max_k) {
    srand(time(0));

    int passed = 0;
    for (int t = 0; t < test_num; t++) {
        // 生成随机数组
        int n = rand() % max_n + 1;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = rand() % max_val + 1;
        }

        // 最大子集数是2^n，但n太大时暴力会超时
        if (n > 15) {
            continue; // 跳过太大的n，暴力枚举会太慢
        }

        int total_subsets = 1 << n;
        int k = rand() % total_subsets + 1;

        vector<ll> res1 = heap_method(nums, k);
        vector<ll> res2 = brute_force(nums, k);

        bool ok = true;
        if (res1.size() != res2.size()) {
            ok = false;
        }
        else {
            for (int i = 0; i < res1.size(); i++) {
                if (res1[i] != res2[i]) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) {
            passed++;
            if (t % 100 == 0) {
                cout << "Test " << t << " passed" << endl;
            }
        }
        else {
            cout << "\nTest " << t << " failed!" << endl;
            cout << "nums: ";
            for (int num : nums) cout << num << " ";
            cout << "\nn = " << n << ", k = " << k << endl;

            cout << "Heap method (" << res1.size() << "): ";
            for (ll val : res1) cout << val << " ";
            cout << "\nBrute force (" << res2.size() << "): ";
            for (ll val : res2) cout << val << " ";
            cout << endl;

            // 详细对比
            cout << "\nDetailed comparison:" << endl;
            int min_len = min(res1.size(), res2.size());
            for (int i = 0; i < min_len; i++) {
                if (res1[i] != res2[i]) {
                    cout << "Difference at index " << i << ": "
                        << res1[i] << " vs " << res2[i] << endl;
                }
            }
            return;
        }
    }

    cout << "\nPassed " << passed << "/" << test_num << " tests!" << endl;
}

// 特定测试用例
void specific_test() {
    cout << "\n=== Specific Tests ===" << endl;

    // 测试1: 简单数组
    {
        vector<int> nums = { 1, 2, 3 };
        int k = 8; // 2^3 = 8个子集
        cout << "\nTest 1: nums = {1, 2, 3}, k = " << k << endl;

        vector<ll> res1 = heap_method(nums, k);
        vector<ll> res2 = brute_force(nums, k);

        cout << "Heap: ";
        for (ll val : res1) cout << val << " ";
        cout << "\nBrute: ";
        for (ll val : res2) cout << val << " ";
        cout << endl;

        if (res1 == res2) {
            cout << "Test 1 passed" << endl;
        }
        else {
            cout << "Test 1 failed" << endl;
        }
    }

    // 测试2: 有重复元素的数组（你的例子）
    {
        vector<int> nums = { 1, 1, 4, 5, 1, 4 };
        int k = 32;
        cout << "\nTest 2: nums = {1, 1, 4, 5, 1, 4}, k = " << k << endl;

        vector<ll> res1 = heap_method(nums, k);
        vector<ll> res2 = brute_force(nums, k);

        // 排序并取前k个（暴力结果已经排序）
        sort(res1.begin(), res1.end());
        if (res1.size() > k) res1.resize(k);
        if (res2.size() > k) res2.resize(k);

        cout << "Heap (first " << min(k, (int)res1.size()) << "): ";
        for (int i = 0; i < min(k, 10); i++) cout << res1[i] << " ";
        if (k > 10) cout << "...";
        cout << "\nBrute (first " << min(k, (int)res2.size()) << "): ";
        for (int i = 0; i < min(k, 10); i++) cout << res2[i] << " ";
        if (k > 10) cout << "...";
        cout << endl;

        bool ok = true;
        int min_len = min(res1.size(), res2.size());
        for (int i = 0; i < min_len; i++) {
            if (res1[i] != res2[i]) {
                ok = false;
                cout << "Difference at index " << i << ": "
                    << res1[i] << " vs " << res2[i] << endl;
                break;
            }
        }

        if (ok && res1.size() == res2.size()) {
            cout << "Test 2 passed" << endl;
        }
        else {
            cout << "Test 2 failed" << endl;
        }
    }

    // 测试3: 全相同元素
    {
        vector<int> nums = { 2, 2, 2 };
        int k = 8; // 2^3 = 8
        cout << "\nTest 3: nums = {2, 2, 2}, k = " << k << endl;

        vector<ll> res1 = heap_method(nums, k);
        vector<ll> res2 = brute_force(nums, k);

        cout << "Heap: ";
        for (ll val : res1) cout << val << " ";
        cout << "\nBrute: ";
        for (ll val : res2) cout << val << " ";
        cout << endl;

        if (res1 == res2) {
            cout << "Test 3 passed" << endl;
        }
        else {
            cout << "Test 3 failed" << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Heap Method vs Brute Force Comparison ===" << endl;

    // 先运行特定测试
    specific_test();

    // 然后运行随机测试
    cout << "\n=== Random Tests ===" << endl;
    cout << "Running random tests (n <= 15 for brute force)..." << endl;

    // 参数：测试次数，最大n，最大值，最大k
    random_test(1000, 10, 10, 100);

    return 0;
}