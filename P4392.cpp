#include <iostream>
#include <cstdio>
using namespace std;
int n, m, c, h = 1, t, hh = 1, tt, q[10005], qq[10005], a[1000005];
bool p = false;
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        while (i - q[h] + 1 > m)
            ++h;
        while (h <= t && a[q[t]] <= a[i])
            --t;
        q[++t] = i;
        while (i - qq[hh] + 1 > m)
            ++hh;
        while (hh <= tt && a[qq[tt]] >= a[i])
            --tt;
        qq[++tt] = i;
        if (i >= m)
            if (a[q[h]] - a[qq[hh]] <= c)
            {
                p = true;
                printf("%d\n", i - m + 1);
            }
    }
    if (!p)
        puts("NONE");
    return 0;
}