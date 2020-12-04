#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, hh = 1, tt;
int a[1000005], st[1000005];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        while (hh <= tt && i - st[hh] + 1 > k)
            ++hh;
        while (hh <= tt && a[i] <= a[st[tt]])
            --tt;
        st[++tt] = i;
        if (i >= k)
            printf("%d ", a[st[hh]]);
    }
    putchar('\n');
    hh = 1;
    tt = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (hh <= tt && i - st[hh] + 1 > k)
            ++hh;
        while (hh <= tt && a[i] >= a[st[tt]])
            --tt;
        st[++tt] = i;
        if (i >= k)
            printf("%d ", a[st[hh]]);
    }
    return 0;
}