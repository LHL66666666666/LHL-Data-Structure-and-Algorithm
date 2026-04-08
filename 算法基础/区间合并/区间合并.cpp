//输入多组区间端点[l,r]
//要求将这些区间有交集的合并为一个区间
//要求返回合并之后的区间个数
//第一行输入n
//接下来n行，每行两个整数l,r，表示区间端点
//输出合并之后的区间个数
//特别地，我们规定只有端点相交的区间也可以合并
//如[1,2],[2,3]可以合并

//模板：第一步按照区间左端点进行排序
//从小到大扫描，维护一个当前的区间
//对于一个左端点，我们维护一个右端点的最大值，直到出现一个左端点大于当前最大的右端点
//再将新的区间变为目前维护的区间
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

// 将所有存在交集的区间合并
void merge(vector<PII>& segs)
{
    vector<PII> res;

    sort(segs.begin(), segs.end());

    int st = -2e9, ed = -2e9;
    for (auto seg : segs) {
        if (ed < seg.first) {
            if (st != -2e9) res.push_back({ st, ed });
            st = seg.first;
            ed = seg.second;
        }
        else {
            ed = max(ed, seg.second);
        }
    }

    if (st != -2e9) res.push_back({ st, ed });

    segs = res;
}

int main()
{
    int n;
    cin >> n;

    vector<PII> segs;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        segs.push_back({ l, r });
    }

    merge(segs);

    cout << segs.size() << endl;

    return 0;
}


//C风格的代码
#include <stdio.h>

#define MAX_N 100010

typedef struct {
    int first;
    int second;
} Pair;

// 比较函数，用于排序
int compare(const void* a, const void* b) {
    Pair* p1 = (Pair*)a;
    Pair* p2 = (Pair*)b;
    if (p1->first != p2->first) {
        return p1->first - p2->first;
    }
    return p1->second - p2->second;
}

// 合并区间函数，返回合并后的区间个数
int merge(Pair segs[], int n) {
    if (n == 0) return 0;

    // 按左端点排序
    qsort(segs, n, sizeof(Pair), compare);

    int count = 1;  // 至少有一个区间
    int st = segs[0].first;
    int ed = segs[0].second;

    for (int i = 1; i < n; i++) {
        if (ed < segs[i].first) {
            // 当前区间与维护区间无交集，开始新的区间
            count++;
            st = segs[i].first;
            ed = segs[i].second;
        }
        else {
            // 有交集，合并区间
            if (segs[i].second > ed) {
                ed = segs[i].second;
            }
        }
    }

    return count;
}

int main() {
    int n;
    Pair segs[MAX_N];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segs[i].first, &segs[i].second);
    }

    int result = merge(segs, n);

    printf("%d\n", result);

    return 0;
}