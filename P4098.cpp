#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, cnt, ans, rt[50005], pre[50005], lst[50005], tr[1750005][2], num[1750005];
struct node
{
    int id;
    int num;
} a[50005];
bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
void insert(int id)
{
    rt[id] = ++cnt;
    int k = rt[id - 1];
    for (int i = 31; i >= 0; --i)
    {
        memcpy(tr[cnt], tr[k], sizeof(tr[k]));
        num[cnt] = num[k];
        ++num[cnt];
        int kk = (a[id].num & (1 << i)) ? 1 : 0;
        tr[cnt][kk] = cnt + 1;
        cnt = tr[cnt][kk];
        k = tr[k][kk];
    }
    ++num[cnt];
    return;
}
int query(int id, int x, int y)
{
    int tot = 0;
    for (int i = 31; i >= 0; --i)
    {
        int k = (a[id].num & (1 << i)) ? 0 : 1;
        if (num[tr[y][k]] - num[tr[x][k]] > 0)
        {
            x = tr[x][k];
            y = tr[y][k];
            tot += (1 << i);
        }
        else
        {
            x = tr[x][k ^ 1];
            y = tr[y][k ^ 1];
        }
    }
    return tot;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d", &a[i].num);
        pre[i] = i - 1;
        lst[i] = i + 1;
    }
    lst[n + 1] = n + 1;
    for (int i = 1; i <= n; ++i)
        insert(i);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        if (lst[a[i].id] != n + 1)
            ans = max(ans, query(i, rt[pre[a[i].id]], rt[lst[lst[a[i].id]] - 1]));
        if (pre[a[i].id])
            ans = max(ans, query(i, rt[max(0, pre[pre[a[i].id]] - 1)], rt[min(lst[a[i].id], n)]));
        pre[lst[a[i].id]] = pre[a[i].id];
        lst[pre[a[i].id]] = lst[a[i].id];
    }
    printf("%d", ans);
    return 0;
}