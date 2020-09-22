#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, num, l, a[100005], b[100005], ans[10005];
char c[100005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d %c", &a[i], &c[i]);
    if (c[1] == '+')
        b[1] = (a[1] + a[n]) % 10;
    else
        b[1] = (a[1] * a[n]) % 10;
    for (int i = 2; i <= n; ++i)
        if (c[i] == '+')
            b[i] = (a[i - 1] + a[i]) % 10;
        else
            b[i] = (a[i - 1] * a[i]) % 10;
    for (int i = 1; i <= m; ++i)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int pos, num;
            char opt;
            scanf("%d%d %c", &pos, &num, &opt);
            ++pos;
            a[pos] = num;
            c[pos] = opt;
            if (pos == 1)
            {
                if (c[1] == '+')
                    b[1] = (a[1] + a[n]) % 10;
                else
                    b[1] = (a[1] * a[n]) % 10;
            }
            else
            {
                if (c[pos] == '+')
                    b[pos] = (a[pos - 1] + a[pos]) % 10;
                else
                    b[pos] = (a[pos - 1] * a[pos]) % 10;
            }
            if (pos == n)
            {
                if (c[1] == '+')
                    b[n] = (a[1] + a[n]) % 10;
                else
                    b[n] = (a[1] * a[n]) % 10;
            }
            else
            {
                if (c[pos + 1] == '+')
                    b[pos + 1] = (a[pos] + a[pos + 1]) % 10;
                else
                    b[pos + 1] = (a[pos] * a[pos + 1]) % 10;
            }
        }
        else
        {
            int pos;
            scanf("%d", &pos);
            ++pos;
            num = 0;
            ans[0] = -1;
            ans[++num] = a[pos];
            for (int j = pos + 1; j != pos; ++j)
            {
                j %= n;
                if (!j)
                    j = n;
                if (j == pos)
                    break;
                ans[++num] = b[j];
            }
            for (int j = 1; j <= n; ++j)
            {
                if (ans[j] && l)
                {
                    ans[0] = max(ans[0], min(l - 1, n - j + 2));
                    l = 0;
                }
                if (!ans[j] && !l)
                    l = j;
            }
            if (!ans[n] && ans[1])
                ans[0] = max(ans[0], 1);
            if (!ans[n] && !ans[1])
                ans[0] = max(ans[0], 0);
            printf("%d\n", ans[0]);
        }
    }
    return 0;
}