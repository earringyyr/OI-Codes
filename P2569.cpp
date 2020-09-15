#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int t, maxn, w, st[2005], f[2005][2005];
int main()
{
    memset(f, 128, sizeof(f));
    scanf("%d%d%d", &t, &maxn, &w);
    for (int i = 1; i <= t; ++i)
    {
        int ap, bp, as, bs;
        scanf("%d%d%d%d", &ap, &bp, &as, &bs);
        for (int j = 0; j <= as; ++j)
            f[i][j] = -j * ap;
        for (int j = 0; j <= maxn; ++j)
            f[i][j] = max(f[i][j], f[i - 1][j]);
        if (i > w)
        {
            int head = 1, tail = 0;
            for (int j = 0; j <= maxn; ++j)
            {
                while (head <= tail && st[head] < j - as)
                    ++head;
                while (head <= tail && f[i - w - 1][st[tail]] + st[tail] * ap <= f[i - w - 1][j] + j * ap)
                    --tail;
                st[++tail] = j;
                f[i][j] = max(f[i][j], f[i - w - 1][st[head]] + st[head] * ap - j * ap);
            }
            head = 1, tail = 0;
            for (int j = maxn; j >= 0; j--)
            {
                while (head <= tail && st[head] > j + bs)
                    ++head;
                while (head <= tail && f[i - w - 1][st[tail]] + st[tail] * bp <= f[i - w - 1][j] + j * bp)
                    --tail;
                st[++tail] = j;
                f[i][j] = max(f[i][j], f[i - w - 1][st[head]] + st[head] * bp - j * bp);
            }
        }
    }
    printf("%d\n", f[t][0]);
    return 0;
}