/*
离散化是一种数据处理的技巧，本质上可以看成是一种 哈希，
其保证数据在哈希以后仍然保持原来的 全/偏序 关系。

通俗地讲就是当有些数据因为本身很大或者类型不支持，
自身无法作为数组的下标来方便地处理，而影响最终结果的只有元素之间的相对大小关系时，
我们可以将原来的数据按照排名来处理问题，即离散化。

用来离散化的可以是大整数、浮点数、字符串等等。
*/
/*
通常原数组中会有重复的元素，一般把相同的元素离散化为相同的数据。

方法如下：

创建原数组的副本。

将副本中的值从小到大排序。

将排序好的副本去重。

查找原数组的每一个元素在副本中的位置，位置即为排名，将其作为离散化后的值
查找时使用二分查找，找到在有序序列中查找第一个不小于指定值的元素也就是lower_bound
*/
// arr[i] 为初始数组,下标范围为 [1, n]

for (int i = 1; i <= n; ++i)  // step 1
tmp[i] = arr[i];
std::sort(tmp + 1, tmp + n + 1);                          // step 2
int len = std::unique(tmp + 1, tmp + n + 1) - (tmp + 1);  // step 3
for (int i = 1; i <= n; ++i)                              // step 4
arr[i] = std::lower_bound(tmp + 1, tmp + len + 1, arr[i]) - tmp;


//acwing模板
vector<int> alls; // 存储所有待离散化的值
sort(alls.begin(), alls.end()); // 将所有值排序
alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 去掉重复元素

// 二分求出x对应的离散化的值
int find(int x) // 找到第一个大于等于x的位置
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}
作者：yxc
链接：https ://www.acwing.com/blog/content/277/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。