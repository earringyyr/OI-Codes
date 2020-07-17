#include <iostream>
#include <cstdio>
using namespace std;
int n, h, t, ans_mi, ans_ma;
int a[1000005], in[1000005];
int dy[1000005], q[1000005];
int flag[1000005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        ++in[a[i]];
    }
    for (int i = 1; i <= n; ++i)
        if (!in[i])
        {
            q[++t] = i;
            ++ans_ma;
        }
    while (h < t)
    {
        ++h;
        int u = q[h];
        int v = a[u];
        if (dy[v])
            continue;
        dy[v] = 1;
        --in[a[v]];
        flag[a[v]] = 1;
        if (!in[a[v]])
            q[++t] = a[v];
    }
    ans_mi = t;
    for (int i = 1; i <= n; ++i)
        if (in[i] && !dy[i])
        {
            int len = 0, en = 0;
            for (int j = i; !dy[j]; j = a[j])
            {
                dy[j] = 1;
                ++len;
                en |= flag[j];
            }
            if (!en && len > 1)
                ++ans_ma;
            ans_mi += len / 2;
        }
    printf("%d %d", n - ans_mi, n - ans_ma);
    return 0;
}