#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, q, ans;
int c[300005], fa[300005], siz[300005], num[300005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)b * a % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
}
int C(int x, int y)
{
    return (ll)c[x] * ksm(c[y], mod - 2) % mod * ksm(c[x - y], mod - 2) % mod;
}
int main()
{
    scanf("%d%d", &n, &q);
    c[0] = 1;
    num[0] = 1;
    siz[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        siz[i] = 1;
        num[i] = 1;
        c[i] = (ll)c[i - 1] * i % mod;
    }
    for (int i = 1; i <= q; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            x = (x + ans) % n;
            y = (y + ans) % n;
            x = getfather(x);
            y = getfather(y);
            fa[x] = y;
            siz[y] += siz[x];
            num[y] = (ll)num[y] * C(siz[y] - 1, siz[x]) % mod * num[x] % mod;
        }
        else
        {
            int x;
            scanf("%d", &x);
            x = (x + ans) % n;
            x = getfather(x);
            ans = num[x];
            printf("%d\n", ans);
        }
    }
    return 0;
}