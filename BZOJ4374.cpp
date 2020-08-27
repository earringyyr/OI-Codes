#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n, m, mid, v[35], p[35], c[35], d[35], top[35];
ll f[35][35];
double ans;
struct node
{
    int c;
    double t;
    node(int aa = 0, double bb = 0)
    {
        c = aa;
        t = bb;
    }
    bool operator<(const node &bb) const
    {
        if (c == bb.c)
            return t < bb.t;
        return c < bb.c;
    }
} q[35][100005];
void dfs1(int k, int cc, int dd, double t)
{
    if (k == mid + 1)
    {
        q[dd][++top[dd]] = node(cc, t);
        return;
    }
    dfs1(k + 1, cc + v[k], dd, t * (double)p[k] / 100);
    dfs1(k + 1, cc, dd + 1, t * (1 - (double)p[k] / 100));
    return;
}
void dfs2(int k, int cc, int dd, double t)
{
    if (k == n + 1)
    {
        for (int i = 0; i <= mid; ++i)
        {
            int lst = 0;
            for (int j = 0; j <= m; ++j)
            {
                int pos = lower_bound(q[i] + 1, q[i] + top[i] + 1, node(f[i + dd][j + 1] - cc, 0)) - q[i];
                ans += j * (q[i][pos - 1].t - q[i][lst].t) * t;
                lst = pos - 1;
                if (lst == top[i])
                    break;
            }
        }
        return;
    }
    dfs2(k + 1, cc + v[k], dd, t * (double)p[k] / 100);
    dfs2(k + 1, cc, dd + 1, t * (1 - (double)p[k] / 100));
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        memset(top, 0, sizeof(top));
        memset(f, 0x7f, sizeof(f));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &v[i], &p[i]);
        for (int i = 1; i <= m; ++i)
            scanf("%d%d", &c[i], &d[i]);
        f[0][0] = 0;
        for (int i = 1; i <= m; ++i)
            for (int j = n; j >= d[i]; --j)
                for (int k = i; k >= 1; --k)
                    f[j][k] = min(f[j][k], f[j - d[i]][k - 1] + c[i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                f[i][j] = min(f[i][j], f[i - 1][j]);
        mid = n / 2;
        dfs1(1, 0, 0, 1);
        for (int i = 0; i <= mid; ++i)
        {
            sort(q[i] + 1, q[i] + top[i] + 1);
            for (int j = 1; j <= top[i]; ++j)
                q[i][j].t += q[i][j - 1].t;
        }
        dfs2(mid + 1, 0, 0, 1);
        printf("%.4f\n", ans);
    }
    return 0;
}