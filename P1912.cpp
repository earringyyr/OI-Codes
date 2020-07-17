#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
char s[100005][50];
int t, n, L, p, head, tail, sum[100005], ans[100005];
long double f[100005];
struct node
{
    int num;
    int l;
    int r;
    node(int aa = 0, int bb = 0, int cc = 0)
    {
        l = aa;
        r = bb;
        num = cc;
    }
} q[100005];
long double ksm(long double a, int k)
{
    long double b = 1;
    while (k)
    {
        if (k & 1)
            b = b * a;
        a = a * a;
        k >>= 1;
    }
    return b;
}
long double val(int i, int j)
{
    return ksm(abs(sum[j] - sum[i] - 1 - L), p);
}
void print(int k)
{
    if (ans[k])
        print(ans[k]);
    for (int i = ans[k] + 1; i < k; ++i)
        printf("%s ", s[i]);
    printf("%s\n", s[k]);
    return;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        head = 1;
        tail = 1;
        scanf("%d%d%d", &n, &L, &p);
        q[1] = node(1, n, 0);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", s[i]);
            sum[i] = sum[i - 1] + strlen(s[i]) + 1;
        }
        for (int i = 1; i <= n; ++i)
        {
            node k = q[head];
            if (k.r == i - 1)
                k = q[++head];
            int j = q[head].num;
            q[head].l = i;
            f[i] = f[j] + val(j, i);
            ans[i] = j;
            k = q[tail];
            int pos = n + 1;
            while (f[i] + val(i, k.l) <= f[k.num] + val(k.num, k.l))
            {
                pos = q[tail].l;
                --tail;
                k = q[tail];
            }
            if (f[i] + val(i, k.r) <= f[k.num] + val(k.num, k.r))
            {
                int l = k.l, r = k.r;
                while (l < r)
                {
                    int mid = (l + r) >> 1;
                    if (f[i] + val(i, mid) > f[k.num] + val(k.num, mid))
                        l = mid + 1;
                    else
                        r = mid;
                }
                q[tail].r = l - 1;
                pos = l;
            }
            if (pos <= n)
                q[++tail] = node(pos, n, i);
        }
        if (f[n] > 1e18)
            puts("Too hard to arrange");
        else
        {
            printf("%lld\n", (long long)(f[n] + 0.5));
            print(n);
        }
        puts("--------------------");
    }
    return 0;
}