/*
位集 Bitset 是一种能以紧凑形式存储位的数据结构。

请你实现 Bitset 类。

Bitset(int size) 用 size 个位初始化 Bitset ，所有位都是 0 。
void fix(int idx) 将下标为 idx 的位上的值更新为 1 。如果值已经是 1 ，则不会发生任何改变。
void unfix(int idx) 将下标为 idx 的位上的值更新为 0 。如果值已经是 0 ，则不会发生任何改变。
void flip() 翻转 Bitset 中每一位上的值。换句话说，所有值为 0 的位将会变成 1 ，反之亦然。
boolean all() 检查 Bitset 中 每一位 的值是否都是 1 。如果满足此条件，返回 true ；否则，返回 false 。
boolean one() 检查 Bitset 中 是否 至少一位 的值是 1 。如果满足此条件，返回 true ；否则，返回 false 。
int count() 返回 Bitset 中值为 1 的位的 总数 。
String toString() 返回 Bitset 的当前组成情况。注意，在结果字符串中，第 i 个下标处的字符应该与 Bitset 中的第 i 位一致。


示例：

输入
["Bitset", "fix", "fix", "flip", "all", "unfix", "flip", "one", "unfix", "count", "toString"]
[[5], [3], [1], [], [], [0], [], [], [0], [], []]
输出
[null, null, null, null, false, null, null, true, null, 2, "01010"]

解释
Bitset bs = new Bitset(5); // bitset = "00000".
bs.fix(3);     // 将 idx = 3 处的值更新为 1 ，此时 bitset = "00010" 。
bs.fix(1);     // 将 idx = 1 处的值更新为 1 ，此时 bitset = "01010" 。
bs.flip();     // 翻转每一位上的值，此时 bitset = "10101" 。
bs.all();      // 返回 False ，bitset 中的值不全为 1 。
bs.unfix(0);   // 将 idx = 0 处的值更新为 0 ，此时 bitset = "00101" 。
bs.flip();     // 翻转每一位上的值，此时 bitset = "11010" 。
bs.one();      // 返回 True ，至少存在一位的值为 1 。
bs.unfix(0);   // 将 idx = 0 处的值更新为 0 ，此时 bitset = "01010" 。
bs.count();    // 返回 2 ，当前有 2 位的值为 1 。
bs.toString(); // 返回 "01010" ，即 bitset 的当前组成情况。
*/
#include <string>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
class Bitset {
public:
    int bitset[N];
    //懒惰标记法
    bool flips;
    int ones;
    int zeros;
    int size_sum;
    Bitset(int size) {
        size_sum = size;
        int s = (size + 31) / 32;
        for (int i = 0; i < s; i++)
        {
            bitset[i] = 0;
        }
        zeros = size;
        ones = 0;
        flips = false;
    }

    void fix(int idx) {
        int idx1 = idx / 32;
        int idx_bit = idx % 32;
        if (!flips)
        {
            //没有反转，含义与初始相同
            //1：存在
            //0：不存在
            if ((bitset[idx1] & (1 << idx_bit)) == 0)
            {
                zeros--;
                ones++;
                bitset[idx1] |= (1 << idx_bit);
            }
            //否则不需要更改
        }
        else {
            //如果经过反转，那么就需要将这个位置的数字更新成0
            //0：存在
            //1：不存在
            if ((bitset[idx1] & (1 << idx_bit)) != 0)
            {
                //我们没有真的反转，需要将1变为0
                //对于他反转意义下的数据相当于0变成1
                //注意这里我们统计1和0的个数要因为反转而改变
                //如果经过反转，我们1的个数变成0的个数，0的个数变成1的个数
                ones++;
                zeros--;
                bitset[idx1] &= (~(1 << idx_bit));
            }
        }

    }

    void unfix(int idx) {
        int idx1 = idx / 32;
        int idx_bit = idx % 32;
        if (!flips)
        {
            //没有反转，含义与初始相同
            //1：存在
            //0：不存在
            if ((bitset[idx1] & (1 << idx_bit)) != 0)
            {
                ones--;
                zeros++;
                bitset[idx1] &= (~(1 << idx_bit));
            }
        }
        else {
            if ((bitset[idx1] & (1 << idx_bit)) == 0)
            {
                //如果经过反转，那么就需要将这个位置的数字更新成1
                //0：存在
                //1：不存在
                ones--;
                zeros++;
                bitset[idx1] |= (1 << idx_bit);
            }
        
        }
    }

    void flip() {
        flips = !flips;
        //交换ones和zeros
        int tmp = ones;
        ones = zeros;
        zeros = tmp;
    }

    bool all() {
        return size_sum == ones;
    }

    bool one() {
        return !(size_sum == zeros);
    }

    int count() {
        return ones;
    }

    string toString() {
        string s;
        int sum = size_sum;
        for (int i = 0; i < (size_sum + 31) / 32; i++)
        {
            if (sum == 0)
            {
                break;
            }
            for (int j = 0; j < 32; j++)
            {
                if ((bitset[i] & (1 << j)) == 0)
                {
                    if (!flips)
                    {
                        s += "0";
                    }
                    else s += "1";
                }
                else {
                    if (!flips)
                    {
                        s += "1";
                    }
                    else s += "0";
                }
                sum--;
                if (sum == 0)
                {
                    break;
                }
            }
            if (sum == 0)
            {
                break;
            }
        }
        return s;
    }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */