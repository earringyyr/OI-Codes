#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt, ans[1005], num[505], s[1005][505], sdk[10][10];
struct node
{
    int l;
    int r;
    int u;
    int d;
    int row;
    int col;
} a[500005];
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
        return true;
    int minx = a[0].r;
    for (int i = a[0].r; i != 0; i = a[i].r)
        if (num[i] < num[minx])
            minx = i;
    remove(minx);
    for (int i = a[minx].d; i != minx; i = a[i].d)
    {
        ans[a[i].row] = 1;
        for (int j = a[i].r; j != i; j = a[j].r)
            remove(a[j].col);
        if (dfs(k + 1))
            return true;
        for (int j = a[i].l; j != i; j = a[j].l)
            restore(a[j].col);
        ans[a[i].row] = 0;
    }
    restore(minx);
    return false;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(s, 0, sizeof(s));
        memset(num, 0, sizeof(num));
        memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= 9; ++i)
            for (int j = 1; j <= 9; ++j)
            {
                char ch;
                scanf(" %c", &ch);
                sdk[i][j] = ch - '0';
            }
        n = 729;
        m = 324;
        for (int i = 1; i <= 9; ++i)
            for (int j = 1; j <= 9; ++j)
                if (!sdk[i][j])
                    for (int k = 1; k <= 9; ++k)
                    {
                        s[9 * (9 * (i - 1) + j - 1) + k][0] = 1;
                        s[9 * (9 * (i - 1) + j - 1) + k][9 * (i - 1) + j] = 1;
                        s[9 * (9 * (i - 1) + j - 1) + k][81 + 9 * (i - 1) + k] = 1;
                        s[9 * (9 * (i - 1) + j - 1) + k][162 + 9 * (j - 1) + k] = 1;
                        s[9 * (9 * (i - 1) + j - 1) + k][243 + 9 * ((i - 1) / 3 * 3 + (j - 1) / 3) + k] = 1;
                    }
                else
                {
                    s[9 * (9 * (i - 1) + j - 1) + sdk[i][j]][0] = 1;
                    s[9 * (9 * (i - 1) + j - 1) + sdk[i][j]][9 * (i - 1) + j] = 1;
                    s[9 * (9 * (i - 1) + j - 1) + sdk[i][j]][81 + 9 * (i - 1) + sdk[i][j]] = 1;
                    s[9 * (9 * (i - 1) + j - 1) + sdk[i][j]][162 + 9 * (j - 1) + sdk[i][j]] = 1;
                    s[9 * (9 * (i - 1) + j - 1) + sdk[i][j]][243 + 9 * ((i - 1) / 3 * 3 + (j - 1) / 3) + sdk[i][j]] = 1;
                }
        init();
        for (int i = 1; i <= n; ++i)
            if (s[i][0])
                add(i);
        dfs(0);
        for (int i = 1; i <= 9; ++i)
        {
            for (int j = 1; j <= 9; ++j)
                for (int k = 1; k <= 9; ++k)
                    if (ans[9 * (9 * (i - 1) + j - 1) + k])
                        printf("%d", k);
            putchar('\n');
        }
    }
    return 0;
}