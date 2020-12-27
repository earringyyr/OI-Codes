#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 200000;
int Q, cnt;
int a[200005];
struct node
{
    char type;
    int i;
    int j;
    int k;
    node(bool aa = 0, int bb = 0, int cc = 0, int dd = 0)
    {
        if (!aa)
            type = '+';
        else
            type = '<';
        i = bb;
        j = cc;
        k = dd;
    }
} ans[200005];
int main()
{
    ans[++Q] = node(0, 0, 1, N - 1);
    ans[++Q] = node(1, N - 2, N - 1, 3);
    ans[++Q] = node(0, 0, 3, N - 2);
    ans[++Q] = node(0, 1, 3, N - 3);
    for (int i = 1; i <= 29; ++i)
        ans[++Q] = node(0, i + 2, i + 2, i + 3);
    cnt = 32;
    for (int i = 29; i >= 0; --i)
    {
        ans[++Q] = node(0, N - 4, i + 3, ++cnt);
        ans[++Q] = node(1, cnt, N - 2, N - 6 - i);
        for (int j = 1; j <= i; ++j)
            ans[++Q] = node(0, N - 6 - i, N - 6 - i, N - 6 - i);
        ans[++Q] = node(0, N - 4, N - 6 - i, N - 4);
        ans[++Q] = node(0, N - 5, i + 3, ++cnt);
        ans[++Q] = node(1, cnt, N - 3, N - 36 - i);
        for (int j = 1; j <= i; ++j)
            ans[++Q] = node(0, N - 36 - i, N - 36 - i, N - 36 - i);
        ans[++Q] = node(0, N - 5, N - 36 - i, N - 5);
    }
    for (int k = 58; k >= 0; --k)
    {
        ans[++Q] = node(0, 2, 2, 2);
        for (int i = max(0, k - 29); i <= min(k, 29); ++i)
        {
            int j = k - i;
            int x = N - 6 - i, y = N - 36 - j;
            ans[++Q] = node(0, x, y, ++cnt);
            ans[++Q] = node(1, max(i, j) + 3, cnt, cnt + 1);
            ++cnt;
            ans[++Q] = node(0, 2, cnt, 2);
        }
    }
    printf("%d\n", Q);
    for (int i = 1; i <= Q; ++i)
        printf("%c %d %d %d\n", ans[i].type, ans[i].i, ans[i].j, ans[i].k);
    return 0;
}