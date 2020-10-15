#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-6;
typedef long long ll;
int n, m, cnt, head, tail;
int l[1505], nxt[1505], num[1505], ans[1505];
int tr[1505][10], pre[1505][1505][2];
double v[1505], f[1505][1505];
char T[1505], s[1505];
bool check(double mid)
{
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= cnt; ++j)
            f[i][j] = -1e14;
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        if (T[i] == '.')
        {
            for (int j = 0; j <= cnt; ++j)
                for (int k = 0; k < 10; ++k)
                {
                    double tmp = v[tr[j][k]] - mid * num[tr[j][k]];
                    if (f[i][tr[j][k]] < f[i - 1][j] + tmp)
                    {
                        f[i][tr[j][k]] = f[i - 1][j] + tmp;
                        pre[i][tr[j][k]][0] = j;
                        pre[i][tr[j][k]][1] = k;
                    }
                }
        }
        else
        {
            int k = T[i] - '0';
            for (int j = 0; j <= cnt; ++j)
            {
                double tmp = v[tr[j][k]] - mid * num[tr[j][k]];
                if (f[i][tr[j][k]] < f[i - 1][j] + tmp)
                {
                    f[i][tr[j][k]] = f[i - 1][j] + tmp;
                    pre[i][tr[j][k]][0] = j;
                    pre[i][tr[j][k]][1] = k;
                }
            }
        }
    for (int i = 0; i <= cnt; ++i)
        if (f[n][i] > 0)
            return true;
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", T + 1);
    for (int i = 1; i <= m; ++i)
    {
        int V;
        scanf("%s%d", s + 1, &V);
        int len = strlen(s + 1);
        int rt = 0;
        for (int j = 1; j <= len; ++j)
        {
            int k = s[j] - '0';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
        }
        v[rt] = log(V);
        num[rt] = 1;
    }
    for (int i = 0; i < 10; ++i)
        if (tr[0][i])
            l[++tail] = tr[0][i];
    while (head < tail)
    {
        int k = l[++head];
        for (int i = 0; i < 10; ++i)
            if (tr[k][i])
            {
                nxt[tr[k][i]] = tr[nxt[k]][i];
                v[tr[k][i]] += v[tr[nxt[k]][i]];
                num[tr[k][i]] += num[tr[nxt[k]][i]];
                l[++tail] = tr[k][i];
            }
            else
                tr[k][i] = tr[nxt[k]][i];
    }
    double l = 0, r = log(1e9);
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    check(l);
    for (int i = 0; i <= cnt; ++i)
        if (f[n][i] > 0)
        {
            int k = i;
            for (int j = n; j >= 1; --j)
            {
                ans[j] = pre[j][k][1];
                k = pre[j][k][0];
            }
            break;
        }
    for (int i = 1; i <= n; ++i)
        printf("%d", ans[i]);
    return 0;
}