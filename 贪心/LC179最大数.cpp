#include<vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    static bool cmp(string& a, string& b) {
        string s1 = a + b, s2 = b + a;
        if (s1 > s2) return 1;
        return 0;
    }
    string largestNumber(vector<int>& nums) {
        //按照字典序排序从大到小输出即可
        vector<string> a;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            a.emplace_back(to_string(nums[i]));
        }
        sort(a.begin(), a.end(), cmp);
        string res = "";
        for (int i = 0; i < n; i++) {
            res += a[i];
            if (res[0] == '0' && a[i] == "0") break;
        }
        return res;
    }
};
/*
对于 nums 中的任意两个值 a 和 b，我们无法直接从常规角度上确定其大小/先后关系。
但我们可以根据「结果」来决定 a 和 b 的排序关系：
如果拼接结果 ab 要比 ba 好，那么我们会认为 a 应该放在 b 前面。
另外，注意我们需要处理前导零（最多保留一位）
*/