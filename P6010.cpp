#include <iostream>
#include <cstdio>
#include <algorithm>
#define eps 1e-10
#define int long long
using namespace std;
int n, l, r, a[200005], q[200005], p[200005], st[200005], fa[200005][20], mo[200005][20];
double calc(int x, int y)
{
    return (double)(a[x] - a[y]) / (x - y);
}
bool upcheck(int x, int y)
{
    if (mo[x][0] == 0)
        return 0;
    double xx = calc(x, mo[x][0]);
    double yy = x * xx - a[x];
    return y * xx - yy - a[y] < -eps;
}
bool downcheck(int x, int y)
{
    if (fa[x][0] == 0)
        return 0;
    double xx = calc(x, fa[x][0]);
    double yy = x * xx - a[x];
    return y * xx - yy - a[y] > eps;
}
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
void write(int x, int y)
{
    int xx = a[x] - a[y];
    int yy = x - y;
    int g = gcd(xx, yy);
    xx /= g;
    yy /= g;
    printf("%lld/%lld\n", xx, yy);
    return;
}
bool cmp(int x, int y)
{
    return a[x] < a[y];
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &q[i]);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    l = 1;
    r = 1;
    st[1] = 0;
    for (int i = n; i >= 1; --i)
    {
        while ((l < r && calc(st[r], p[i]) < 0) || (l + 1 < r && calc(st[r], p[i]) > calc(st[r - 1], st[r])))
            --r;
        fa[p[i]][0] = st[r];
        st[++r] = p[i];
    }
    for (int i = 1; i <= 18; ++i)
        for (int j = 1; j <= n; ++j)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
    l = 1;
    r = 1;
    st[1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while ((l < r && calc(st[r], p[i]) < 0) || (l + 1 < r && calc(st[r], p[i]) > calc(st[r - 1], st[r])))
            --r;
        mo[p[i]][0] = st[r];
        st[++r] = p[i];
    }
    for (int i = 1; i <= 18; ++i)
        for (int j = 1; j <= n; ++j)
            mo[j][i] = mo[mo[j][i - 1]][i - 1];
    for (int i = 1; i <= n; ++i)
        if (a[q[i]] < a[i])
        {
            int id = i;
            if (downcheck(i, q[i]))
            {
                for (int j = 18; j >= 0; --j)
                    if (downcheck(fa[id][j], q[i]))
                        id = fa[id][j];
                id = fa[id][0];
                if (id < q[i])
                    puts("-1");
                else
                    write(id, q[i]);
            }
            else if (i < q[i])
                puts("-1");
            else
                write(i, q[i]);
        }
        else
        {
            int id = i;
            if (upcheck(i, q[i]))
            {
                for (int j = 18; j >= 0; --j)
                    if (upcheck(mo[id][j], q[i]))
                        id = mo[id][j];
                id = mo[id][0];
                if (id > q[i])
                    puts("-1");
                else
                    write(id, q[i]);
            }
            else if (i > q[i])
                puts("-1");
            else
                write(i, q[i]);
        }
    return 0;
}