#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
#define mp make_pair
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 0x7fffffff;
int n;
int X[200005], Y[200005];
int L[200005], R[200005];
ll ans[200005];
map<pii, ll> f[2];
struct node
{
    int id;
    int x;
    int y;
} a[200005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int dis(int x, int y)
{
    return abs(X[a[x].x] - X[a[y].x]) + abs(Y[a[x].y] - Y[a[y].y]);
}
ll dfs(int l, int r, int u, int d, int type)
{
    map<pii, ll>::iterator it = f[type].find(mp(l, r));
    if (it != f[type].end())
        return it->second;
    int nl = L[l - 1], nr = R[r + 1];
    ll minx = 1e18;
    if (l > 1 && (a[l - 1].y == u + 1 || a[l - 1].y == d - 1))
        minx = min(minx, dis(nl, type ? r : l) + dfs(nl, r, max(u, a[nl].y), min(d, a[nl].y), 0));
    if (r < n && (a[r + 1].y == u + 1 || a[r + 1].y == d - 1))
        minx = min(minx, dis(nr, type ? r : l) + dfs(l, nr, max(u, a[nr].y), min(d, a[nr].y), 1));
    if (minx == 1e18)
        f[type][mp(l, r)] = l - r;
    else
        f[type][mp(l, r)] = minx;
    return f[type][mp(l, r)];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        scanf("%d%d", &a[i].x, &a[i].y);
        X[i] = a[i].x;
        Y[i] = a[i].y;
    }
    sort(X + 1, X + n + 1);
    sort(Y + 1, Y + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i].x = lower_bound(X + 1, X + n + 1, a[i].x) - X;
        a[i].y = lower_bound(Y + 1, Y + n + 1, a[i].y) - Y;
    }
    sort(a + 1, a + n + 1, cmp);
    L[1] = 1;
    for (int i = 2; i <= n; ++i)
        if (abs(a[i].y - a[i - 1].y) == 1)
            L[i] = L[i - 1];
        else
            L[i] = i;
    R[n] = n;
    for (int i = n - 1; i >= 1; --i)
        if (abs(a[i].y - a[i + 1].y) == 1)
            R[i] = R[i + 1];
        else
            R[i] = i;
    for (int i = 1; i <= n; ++i)
        ans[a[i].id] = dfs(i, i, a[i].y, a[i].y, 0);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}