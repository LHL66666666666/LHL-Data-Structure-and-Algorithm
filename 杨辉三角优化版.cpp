#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        int arr[40][40];
        for (int i = 1; i <= rowIndex + 1; i++)
        {
            arr[i][1] = 1;
        }
        for (int i = 2; i <= rowIndex + 1; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
            }
        }
        vector<int> ret;
        for (int i = 1; i <= rowIndex + 1; i++)
        {
            ret.push_back(arr[rowIndex + 1][i]);
        }
        return ret;
    }
};

int main()
{
    //注意杨辉三角如何初始化和递推的
    //计算组合数公式也可以用相似的方法

    //注意到对第 i+1 行的计算仅用到了第 i 行的数据，
    // 因此可以使用滚动数组的思想优化空间复杂度。
    //始终只存储两行的数据，优化了空间复杂度
   /*class Solution {
    public:
        vector<int> getRow(int rowIndex) {
            vector<int> pre, cur;
            for (int i = 0; i <= rowIndex; ++i) {
                cur.resize(i + 1);
                cur[0] = cur[i] = 1;
                //这边把首尾都提前赋值，因为pre的长度始终比cur少一，最后一位计算时会越界
                for (int j = 1; j < i; ++j) {
                    cur[j] = pre[j - 1] + pre[j];
                }
                pre = cur;
            }
            return pre;
        }
    };
    */
    //


    //使用二维数组进行的优化
    //也是基于滚动数组的思想
    //class Solution {
    //public:
    //    vector<int> getRow(int rowIndex) {

    //        vector<int> ret;
    //        //二维数组
    //        int arr[2][40];
    //        //只开两行，一行存储pre，另一行存储now
    //        //使pre和now交替，就不用开新的行，节省空间
    //        int pre = 0;
    //        int now = 1;
    //        arr[pre][0] = 1;
    //        这里首先确保第一行有元素，不然无法递推
    //        for (int i = 0; i <= rowIndex; i++)
    //        {
    //            for (int j = 0; j <= i; j++)
    //            {
    //                if (j == 0 || j == i)
    //                {
    //                    arr[now][j] = 1;
    //                    //确保不越界
    //                }
    //                else {
    //                    arr[now][j] = arr[pre][j] + arr[pre][j - 1];
    //                }
    //            }
    //            //实现pre和now二者交换
    //            //事实上，pre和now交替作为0、1
    //            pre = 1 - pre;
    //            now = 1 - now;

    //        }
    //        //注意最后一次循环结束后，依然执行了pre和now的交换，因此输出的应该是pre
    //        for (int i = 0; i <= rowIndex; i++)
    //        {
    //            ret.push_back(arr[pre][i]);
    //        }
    //        return ret;
    //    }
    //};
    return 0;
}