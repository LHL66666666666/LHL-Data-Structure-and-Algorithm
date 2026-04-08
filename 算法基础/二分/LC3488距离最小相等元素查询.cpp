#include <vector>
using namespace std;
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        vector<int> ret;
        vector<int> nums2;
        //环形数组，最好将环形拆成链
        //扩展到原来的两倍即可
        int n = nums.size();
        int m = queries.size();
        for (int i = 0; i < 2 * n; i++)
        {
            if (i < n)
            {
                nums2.push_back(nums[i]);
            }
            else {
                nums2.push_back(nums[i - n]);
            }
        }
        //转换环变为链

    }
};