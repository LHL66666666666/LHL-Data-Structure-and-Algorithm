/*
这里有 n 个航班，它们分别从 1 到 n 进行编号。

有一份航班预订表 bookings ，表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] 意味着在从 firsti 到 lasti （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。

请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数
*/
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n + 1, 0);  // 差分数组，多开一个位置

        // 第一步：只进行差分标记
        for (const auto& booking : bookings) {
            int a = booking[0] - 1;  // 转换为0-based索引
            int b = booking[1] - 1;
            int c = booking[2];

            diff[a] += c;
            if (b + 1 < n) {  // 注意这里要判断b+1是否越界
                diff[b + 1] -= c;
            }
        }

        // 第二步：一次性计算前缀和得到最终结果
        vector<int> result(n);
        result[0] = diff[0];
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] + diff[i];
        }

        return result;
    }
};