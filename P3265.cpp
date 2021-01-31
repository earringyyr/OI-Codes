#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-6;
int n, m, cnt, ans;
long double w[505][505];
struct node
{
    long double a[505];
    int c;
} z[505];
bool cmp(node aa, node bb)
{
    return aa.c < bb.c;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%Lf", &z[i].a[j]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &z[i].c);
    sort(z + 1, z + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (fabs(z[i].a[j]) > eps)
            {
                if (fabs(w[j][j]) < eps)
                {
                    for (int k = 1; k <= m; ++k)
                        w[j][k] = z[i].a[k];
                    ++cnt;
                    ans += z[i].c;
                    break;
                }
                double t = z[i].a[j] / w[j][j];
                for (int k = j; k <= m; ++k)
                    z[i].a[k] -= t * w[j][k];
            }
    printf("%d %d", cnt, ans);
    return 0;
}