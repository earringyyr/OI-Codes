#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define eps 0.000001
#define int long long
using namespace std;
int n, m, s, x, ans, cnt[2], goa[100005], gob[100005], pos[100005], lg[100005], da[100005][30], db[100005][30], fa[100005][30];
double minx = 1000000000000;
struct node
{
    int id;
    int l;
    int r;
    int h;
} a[100005];
bool cmp(node aa, node bb)
{
    return aa.h < bb.h;
}
bool dire(int id)
{
    if (!a[id].r)
        return 1;
    if (!a[id].l)
        return 0;
    return abs(a[id].h - a[a[id].l].h) <= abs(a[id].h - a[a[id].r].h);
}
int colc(int id, int x, int y)
{
    if (!x)
        return a[y].id;
    if (!y)
        return a[x].id;
    if (abs(a[id].h - a[x].h) <= abs(a[id].h - a[y].h))
        return a[x].id;
    return a[y].id;
}
void solve(int id)
{
    int xx = x;
    memset(cnt, 0, sizeof(cnt));
    for (int i = lg[n]; i >= 0; --i)
    {
        if (fa[id][i] && da[id][i] + db[id][i] <= xx)
        {
            xx -= da[id][i] + db[id][i];
            cnt[0] += da[id][i];
            cnt[1] += db[id][i];
            id = fa[id][i];
        }
    }
    if (goa[id] && da[id][0] <= xx)
        cnt[0] += da[id][0];
    return;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; i++)
    {
        a[i].id = i;
        scanf("%lld", &a[i].h);
    }
    sort(a + 1, a + n + 1, cmp);
    ans = a[n].id;
    for (int i = 1; i <= n; ++i)
        pos[a[i].id] = i;
    for (int i = 1; i <= n; ++i)
    {
        a[i].l = i - 1;
        a[i].r = i + 1;
    }
    a[1].l = 0;
    a[n].r = 0;
    for (int i = 1; i <= n; ++i)
    {
        int id = pos[i];
        if (dire(id))
        {
            goa[i] = colc(id, a[a[id].l].l, a[id].r);
            gob[i] = a[a[id].l].id;
        }
        else
        {
            goa[i] = colc(id, a[id].l, a[a[id].r].r);
            gob[i] = a[a[id].r].id;
        }
        if (a[id].l)
            a[a[id].l].r = a[id].r;
        if (a[id].r)
            a[a[id].r].l = a[id].l;
    }
    for (int i = 1; i <= n; ++i)
    {
        fa[i][0] = gob[goa[i]];
        da[i][0] = abs(a[pos[i]].h - a[pos[goa[i]]].h);
        db[i][0] = abs(a[pos[fa[i][0]]].h - a[pos[goa[i]]].h);
    }
    for (int j = 1; j <= lg[n]; ++j)
        for (int i = 1; i <= n; ++i)
        {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            da[i][j] = da[i][j - 1] + da[fa[i][j - 1]][j - 1];
            db[i][j] = db[i][j - 1] + db[fa[i][j - 1]][j - 1];
        }
    scanf("%lld", &x);
    for (int i = n; i >= 1; --i)
    {
        solve(a[i].id);
        if (cnt[1] && ((double)cnt[0] / cnt[1] < minx))
        {
            minx = (double)cnt[0] / cnt[1];
            ans = a[i].id;
        }
    }
    printf("%lld\n", ans);
    scanf("%lld", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%lld%lld", &s, &x);
        solve(s);
        printf("%lld %lld\n", cnt[0], cnt[1]);
    }
    return 0;
}