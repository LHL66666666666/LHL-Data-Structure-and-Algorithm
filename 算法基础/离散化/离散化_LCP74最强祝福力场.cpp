/*
小扣在探索丛林的过程中，无意间发现了传说中“落寞的黄金之都”。而在这片建筑废墟的地带中，小扣使用探测仪监测到了存在某种带有「祝福」效果的力场。 经过不断的勘测记录，小扣将所有力场的分布都记录了下来。forceField[i] = [x,y,side] 表示第 i 片力场将覆盖以坐标 (x,y) 为中心，边长为 side 的正方形区域。

若任意一点的 力场强度 等于覆盖该点的力场数量，请求出在这片地带中 力场强度 最强处的 力场强度。

注意：

力场范围的边缘同样被力场覆盖。
*/
long long sx[205];
long long sy[205];
int ret[205][205];
class Solution {
public:
    int binS(long long a[], long long target,int size)
    {
        int l = 0, r = size - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (a[mid] >= target)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans + 1;
    }
    // 标准去重函数
    int unique(long long a[], int size) {
        if (size == 0) return 0;
        int cnt = 0;
        for (int i = 1; i < size; i++) {
            if (a[i] != a[cnt]) {
                cnt++;
                a[cnt] = a[i];
            }
        }
        //查找到的下标要加1，为了对应1-based下标
        return cnt + 1;
    }
    void set(int a[][205], int x1, int y1, int x2, int y2)
    {
        //这里形参是1-based下标
        a[x1][y1] += 1;
        a[x2 + 1][y2 + 1] += 1;
        a[x2 + 1][y1] -= 1;
        a[x1][y2 + 1] -= 1;
    }
    void build(int a[][205],int sizex,int sizey)
    {
        for (int i = 1; i <=sizex+1; i++)
        {
            for (int j = 1; j <=sizey+1; j++)
            {
                a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j];
            }
        }
    }

    int fieldOfGreatestBlessing(vector<vector<int>>& forceField) {
        //破案了，错误出在这里
        //数组开在全局的时候记得每次初始化
        //初始化
        memset(ret, 0, sizeof(ret));
        //边长side是一个整数，除以2之后可能会出现0.5这样的实数，不好操作下标
        //我们首先进行扩大处理
        //将坐标轴整体进行伸缩，x变为原来的2倍，side变为2倍，就可以保证不出现0.5
        //同时，所有参数都变为两倍，不会影响不同区域间的相对位置关系，
        //也就是说互相覆盖或不覆盖的关系
        //令side=r
        //变换：左边界：2*x-r,右边界：2*x+r
        //上边界：2*y+r,下边界：2*y-r
        //也就是说，原来的(x,y,side)转换为(2x,2y,2side)
        //但是这样也存在问题：当数据很大时，内存空间不够
        //因此，本题目需要离散化，本质上是哈希
        //将物理坐标转换为逻辑坐标
        //只需要按照x，y的大小依次编号，
        //就能表示出每一个矩形之间的位置关系，建立映射即可
        //原矩阵初始都是0，直接二维差分即可
        int n = forceField.size();
        //一个位置对应x两个边界，y两个边界
        for (int i = 0; i < n; i++)
        {
            long long x = forceField[i][0];
            long long y = forceField[i][1];
            long long r = forceField[i][2];
            //先开2个数组存起来边界，存x和y，排序，再去重，再哈希
            sx[i] = 2 * x - r;
            sx[i + n] = 2 * x + r;
            sy[i] = 2 * y - r;
            sy[i + n] = 2 * y + r;
        }
        //排序
        sort(sx, sx + 2 * n);
        sort(sy, sy + 2 * n);
        //去重,原地修改
        //返回值是有效长度
        int sizex=unique(sx,2*n);
        int sizey=unique(sy,2*n);
        //再次处理每个数据，每次二分查找四个边界的下标，然后对它进行差分
        for (int i = 0; i < n; i++)
        {
            long long x = forceField[i][0];
            long long y = forceField[i][1];
            long long r = forceField[i][2];
            long long x1 = 2 * x - r;
            long long x2 = 2 * x + r;
            long long y1 = 2 * y - r;
            long long y2 = 2 * y + r;
            x1 = binS(sx, x1,sizex);
            x2 = binS(sx, x2,sizex);
            y1 = binS(sy, y1,sizey);
            y2 = binS(sy, y2,sizey);
            set(ret, x1, y1, x2, y2);
        }
        build(ret, sizex, sizey);
        int res = 0;
        for (int i = 1; i <= sizex; i++)
        {
            for (int j = 1; j <=  sizey; j++)
            {
                res = (res > ret[i][j] ? res : ret[i][j]);
            }
        }
        return res;
    }
};
//时间复杂度O(Nlogn+M^2)

//另一题解
class Solution {
public:


    //排序以后去重
    //i会来到第一个和size处不相等的位置，然后拷贝
    int sort_(vector<long long>& nums)
    {
        sort(nums.begin(), nums.end());
        int size = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] != nums[size - 1])
            {
                //i和size其实保持同步的，只有在i和前一个元素不一样才同步，换言之，一样的话i会往前走
                nums[size++] = nums[i];
            }
        }
        return size;
    }

    //查找下标+1的位置，因为我们的差分数组外围都是一圈的0，需要用下标+1的来构建差分数组。
    int rank(vector<long long>& nums, long long v, int size)
    {
        int l = 0;
        int r = size - 1;
        int m, ans = 0;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (nums[m] >= v)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans + 1;
    }


    //差分，这里给的是左下角点和右上角点
    void add(vector<vector<int>>& diff, int a, int b, int c, int d)
    {
        diff[a][b] += 1;
        diff[c + 1][d + 1] += 1;
        diff[c + 1][b] -= 1;
        diff[a][d + 1] -= 1;
    }


    int fieldOfGreatestBlessing(vector<vector<int>>& f)
    {
        int n = f.size();
        //力场的个数n

        vector<long long> xs(2 * n);
        vector<long long> ys(2 * n);

        for (int i = 0, k = 0, p = 0; i < n; ++i)
        {
            long long x = f[i][0];
            long long y = f[i][1];
            long long r = f[i][2];

            //上下左右边界全存进数组里
            xs[k++] = x * 2 - r;
            xs[k++] = x * 2 + r;
            ys[p++] = y * 2 - r;
            ys[p++] = y * 2 + r;
        }

        //去重以后的排序的数组
        int sizex = sort_(xs);
        int sizey = sort_(ys);

        //差分数组
        vector<vector<int>> diff(sizex + 2, vector<int>(sizey + 2, 0));
        for (int i = 0, a, b, c, d; i < n; ++i)
        {
            //为什么可以用rank来代替真实的坐标呢？
            //因为rank以后，矩阵形状虽然被压缩了，但是矩阵与矩阵的相邻状态并没有改变
            //就行几块重叠的橡皮，你拉升压缩，它重叠的部分依然是那块。
            long long x = f[i][0];
            long long y = f[i][1];
            long long r = f[i][2];


            a = rank(xs, 2 * x - r, sizex);
            b = rank(ys, 2 * y - r, sizey);
            c = rank(xs, 2 * x + r, sizex);
            d = rank(ys, 2 * y + r, sizey);

            //把每个力场内部都加1
            add(diff, a, b, c, d);
        }

        int ans = 0;
        for (int i = 1; i < diff.size(); ++i)
        {
            for (int j = 1; j < diff[0].size(); ++j)
            {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
                ans = max(ans, diff[i][j]);
            }
        }
        return ans;
    }
};
