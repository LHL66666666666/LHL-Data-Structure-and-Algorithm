//给定一个包含 n 个整数的数组 nums，
//判断 nums 中是否存在三个元素 a ，b ，c ，
//使得 a + b + c = 0 ？
//请找出所有和为 0 且 不重复 的三元组。
//考虑将问题降维，三数之和能否变为两数？
//再开一个数组存储原数组每个数字的相反数
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        if (n < 3) return ret;

        // 正确排序
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            // 跳过重复的i
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int target = -nums[i]; // a + b + c = 0 => b + c = -a
            int l = i + 1, r = n - 1;

            while (l < r) {
                int sum = nums[l] + nums[r];

                if (sum < target) {
                    l++;
                }
                else if (sum > target) {
                    r--;
                }
                else {
                    // 找到符合条件的三个数
                    ret.push_back({ nums[i], nums[l], nums[r] });

                    // 跳过重复的l和r
                    while (l < r && nums[l] == nums[l + 1]) l++;
                    while (l < r && nums[r] == nums[r - 1]) r--;

                    l++;
                    r--;
                }
            }
        }
        return ret;
    }
};

//重写一下
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        //为了防止爆内存，不再开一个新数组
        //a+b+c=0等价于b+c=-a
        //如果不够三个数，直接返回空
        int n = nums.size();
        if (n < 3)
        {
            return ret;
        }
        //遍历一次数组，先获取a
        //先排序，这是使用左右指针的前提
        sort(nums.begin(), nums.end());
        // 先排序，保证 a ≤ b ≤ c 的基础
        for (int i = 0; i < n; i++)
        {
            int tmp;
            //tmp存储-a，且注意要避免重复
            // 跳过相同的a
            if (i == 0)
            {
                tmp = -nums[0];
            }
            else if (i > 0 && nums[i] != nums[i - 1])
            {
                tmp = -nums[i];
            }
            else continue;
            //要注意，-a不能重复，b+c也不能重复
            //左右指针
            //l要从i+1开始，
            //防止同一个元素被使用两次
            //a,b,c是等价的，都需要避免重复使用
            int l = i + 1, r = n - 1;
            // 这里隐含了 i < l < r，即 a ≤ b ≤ c
            while (l < r)
            {
                if (nums[l] + nums[r] < tmp)
                {
                    l++;
                }
                else if (nums[l] + nums[r] > tmp)
                {
                    r--;
                }
                else
                {
                    ret.push_back({ nums[l],nums[r],-tmp });
                    //更新l，r注意要跳过重复元素
                    //还要控制l<r
                    while (l<r && nums[l + 1] == nums[l])
                    {
                        l++;
                    }
                    while (l<r && nums[r - 1] == nums[r])
                    {
                        r--;
                    }
                    l++;
                    r--;
                }
                
            }

        }
        return ret;
    }
};

//题解：
//本题同时使用了双指针用于去重和用于查找两数之和
//「不重复」的本质是什么？我们保持三重循环的大框架不变，只需要保证：
//
//第二重循环枚举到的元素不小于当前第一重循环枚举到的元素；
//
//第三重循环枚举到的元素不小于当前第二重循环枚举到的元素。
//
//也就是说，我们枚举的三元组(a, b, c) 满足 a≤b≤c，保证了只有(a, b, c) 这个顺序会被枚举到，
//而(b, a, c)、(c, b, a) 等等这些不会，这样就减少了重复。
//同时注意：a,b,c等价
//要实现这一点，我们可以将数组中的元素从小到大进行排序，随后使用普通的三重循环就可以满足上面的要求。
//
//同时，对于每一重循环而言，相邻两次枚举的元素不能相同，否则也会造成重复。举个例子，如果排完序的数组为
//[0, 1, 2, 2, 2, 3]
// ^  ^  ^
//我们使用三重循环枚举到的第一个三元组为(0, 1, 2)，如果第三重循环继续枚举下一个元素，
//那么仍然是三元组(0, 1, 2)，产生了重复。因此我们需要将第三重循环「跳到」下一个不相同的元素，
//即数组中的最后一个元素 3，枚举三元组(0, 1, 3)

   
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // 先排序，保证 a ≤ b ≤ c 的基础
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({ nums[first], nums[second], nums[third] });
                }
            }
        }
        return ans;
    }
};