#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
const double eps = 1e-8;
int n, m;
double l[15][15];
signed main()
{
    int T;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                l[i][j] = 0;
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%lld%lld", &u, &v);
            --l[u][v];
            --l[v][u];
            ++l[u][u];
            ++l[v][v];
        }
        --n;
        for (int i = 1; i <= n; ++i)
        {
            int maxn = i;
            for (int j = i + 1; j <= n; ++j)
                if (l[j][i] > l[maxn][i])
                    maxn = j;
            if (maxn != i)
                for (int j = 1; j <= n; ++j)
                    swap(l[i][j], l[maxn][j]);
            if (fabs(l[i][i]) < eps)
                break;
            for (int j = i + 1; j <= n; ++j)
            {
                double t = l[j][i] / l[i][i];
                for (int k = i; k <= n; ++k)
                    l[j][k] -= l[i][k] * t;
            }
        }
        double ans = 1;
        for (int i = 1; i <= n; ++i)
            ans *= l[i][i];
        printf("%.0f\n", fabs(ans));
    }
    return 0;
}