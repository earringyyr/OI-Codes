#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
int n, h, r, fa[1005], x[1005], y[1005], z[1005];
int getfather(int k)
{
    if (fa[k] == k)
        return k;
    fa[k] = getfather(fa[k]);
    return fa[k];
}
bool jiao(int a, int b)
{
    return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]) + (z[a] - z[b]) * (z[a] - z[b]) <= 4 * r * r;
}
signed main()
{
    int t;
    scanf("%lld", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%lld%lld%lld", &n, &h, &r);
        for (int i = 1; i <= n + 2; ++i)
            fa[i] = i;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
            for (int j = 1; j < i; ++j)
                if (jiao(i, j) && getfather(i) != getfather(j))
                    fa[getfather(i)] = getfather(j);
            if (z[i] - r <= 0 && getfather(i) != getfather(n + 1))
                fa[getfather(i)] = getfather(n + 1);
            if (z[i] + r >= h && getfather(i) != getfather(n + 2))
                fa[getfather(i)] = getfather(n + 2);
        }
        if (getfather(n + 1) == getfather(n + 2))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}