#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, sum, cnt, a[200005], type[200005], rt[200005];
struct tree
{
    int l;
    int r;
    int num;
    int sum;
} tr[25 * 200005];
void build(int &id, int l, int r)
{
    id = ++cnt;
    tr[id].num = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(tr[id].l, l, mid);
    build(tr[id].r, mid + 1, r);
    return;
}
void add(int &y, int x, int l, int r, int w, int val)
{
    y = ++cnt;
    tr[y] = tr[x];
    ++tr[y].num;
    if (l == r)
    {
        tr[y].sum = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[y].l, tr[x].l, l, mid, w, val);
    else
        add(tr[y].r, tr[x].r, mid + 1, r, w, val);
    return;
}
int ask(int id, int l, int r, int val)
{
    if (l == r)
        return tr[id].sum;
    int mid = (l + r) >> 1;
    if (tr[tr[id].l].num >= val)
        return ask(tr[id].l, l, mid, val);
    else
        return ask(tr[id].r, mid + 1, r, val - tr[tr[id].l].num);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        cnt = 0;
        scanf("%d", &n);
        build(rt[0], 1, n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d", &type[i], &a[i]);
            if (type[i] == 1)
            {
                ++sum;
                add(rt[sum], rt[sum - 1], 1, n, i, a[i]);
            }
            else if (type[i] == 2)
            {
                ++sum;
                rt[sum] = rt[sum - a[i] - 1];
            }
            else if (type[i] == 3)
                printf("%d\n", ask(rt[sum], 1, n, a[i]));
        }
    }
    return 0;
}
