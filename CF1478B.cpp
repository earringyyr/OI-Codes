#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int q, d;
int minx[15];
int a[10005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &q, &d);
        for (int i = 0; i < d; ++i)
        {
            int now = i, cnt = 0;
            while (now && cnt < 10)
            {
                now = (now + d) % 10;
                ++cnt;
            }
            if (cnt == 10)
                minx[i] = cnt * d + i;
            else
                minx[i] = cnt * d + i + d;
        }
        for (int i = 1; i <= q; ++i)
        {
            scanf("%d", &a[i]);
            if (a[i] >= minx[a[i] % d])
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}