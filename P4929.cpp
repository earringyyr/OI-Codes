#include <iostream>
#include <cstdio>
using namespace std;
int n, m, cnt, sum, ans[505], num[505], s[505][505];
struct node
{
    int l;
    int r;
    int u;
    int d;
    int row;
    int col;
} a[250005];
void init()
{
    for (int i = 0; i <= m; ++i)
    {
        a[i].l = i - 1;
        a[i].r = i + 1;
        a[i].u = i;
        a[i].d = i;
    }
    a[0].l = m;
    a[m].r = 0;
    cnt = m + 1;
    return;
}
void add(int k)
{
    int first = cnt;
    for (int i = 1; i <= m; ++i)
        if (s[k][i])
        {
            a[cnt].l = cnt - 1;
            a[cnt].r = cnt + 1;
            a[cnt].u = a[i].u;
            a[cnt].d = i;
            a[a[cnt].u].d = cnt;
            a[i].u = cnt;
            a[cnt].row = k;
            a[cnt].col = i;
            ++num[i];
            ++cnt;
        }
    a[cnt - 1].r = first;
    a[first].l = cnt - 1;
    return;
}
void remove(int k)
{
    a[a[k].l].r = a[k].r;
    a[a[k].r].l = a[k].l;
    for (int i = a[k].d; i != k; i = a[i].d)
        for (int j = a[i].r; j != i; j = a[j].r)
        {
            a[a[j].u].d = a[j].d;
            a[a[j].d].u = a[j].u;
            --num[a[j].col];
        }
    return;
}
void restore(int k)
{
    for (int i = a[k].u; i != k; i = a[i].u)
        for (int j = a[i].l; j != i; j = a[j].l)
        {
            a[a[j].d].u = j;
            a[a[j].u].d = j;
            ++num[a[j].col];
        }
    a[a[k].l].r = k;
    a[a[k].r].l = k;
    return;
}
bool dfs(int k)
{
    if (a[0].r == 0)
    {
        sum = k;
        return true;
    }
    int mi = a[0].r;
    for (int i = a[0].r; i != 0; i = a[i].r)
        if (num[i] < num[mi])
            mi = i;
    remove(mi);
    for (int i = a[mi].d; i != mi; i = a[i].d)
    {
        ans[k + 1] = a[i].row;
        for (int j = a[i].r; j != i; j = a[j].r)
            remove(a[j].col);
        if (dfs(k + 1))
            return true;
        for (int j = a[i].l; j != i; j = a[j].l)
            restore(a[j].col);
    }
    restore(mi);
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &s[i][j]);
    for (int i = 1; i <= n; ++i)
        add(i);
    if (dfs(0))
        for (int i = 1; i <= sum; ++i)
            printf("%d ", ans[i]);
    else
        puts("No Solution!");
    return 0;
}