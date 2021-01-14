#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, cnt, tot, lst = 1, col, ans;
int a[55], b[55], vis[55];
int fa[55], siz[55];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void dfs(int k, int lst, int num, int col, int sum)
{
    if (!num)
    {
        if (k == n)
        {
            ans = (ans + col) % mod;
            return;
        }
        if (sum - a[k] > 0)
        {
            b[++m] = sum - a[k];
            dfs(k + 1, 1, a[k + 1], col, 0);
            --m;
        }
        return;
    }
    int co = 0;
    for (int i = lst + 1; i <= m; ++i)
        if (!vis[i])
            ++co;
    if (co >= num)
        dfs(k, lst + 1, num, col, sum);
    if (!vis[lst])
    {
        vis[lst] = 1;
        dfs(k, lst + 1, num - 1, (ll)col * num % mod * b[lst] % mod, sum + b[lst]);
        vis[lst] = 0;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u = getfather(u);
        v = getfather(v);
        if (u != v)
            fa[u] = v;
    }
    for (int i = 1; i <= n - m - 1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u = getfather(u + n);
        v = getfather(v + n);
        if (u != v)
            fa[u] = v;
    }
    for (int i = 1; i <= 2 * n; ++i)
        ++siz[getfather(i)];
    for (int i = 1; i <= n; ++i)
        if (getfather(i) == i)
        {
            if (siz[i] == 1)
                ++tot;
            else
                a[++cnt] = siz[i];
        }
    m = cnt;
    cnt = 0;
    for (int i = n + 1; i <= 2 * n; ++i)
        if (getfather(i) == i)
            b[++cnt] = siz[i];
    n = cnt;
    swap(m, n);
    sort(a + 1, a + n + 1, cmp);
    dfs(1, 1, a[1], 1, 0);
    tot = max(tot, 1);
    for (int i = 1; i <= tot; ++i)
        ans = (ll)ans * i % mod;
    printf("%d", ans);
    return 0;
}