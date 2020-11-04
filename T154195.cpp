#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, rt, cnt;
int siz[1005], f[1005];
int c[1005][1005];
struct node
{
    int l;
    int r;
    int num;
} tr[1005];
void insert(int val)
{
    int u = rt, v = 0;
    while (u)
    {
        v = u;
        if (val < tr[u].num)
            u = tr[u].l;
        else
            u = tr[u].r;
    }
    ++cnt;
    tr[cnt].l = 0;
    tr[cnt].r = 0;
    tr[cnt].num = val;
    if (v)
    {
        if (val < tr[v].num)
            tr[v].l = cnt;
        else
            tr[v].r = cnt;
    }
    if (cnt == 1)
        rt = 1;
    return;
}
void dfs(int k)
{
    f[k] = 1;
    siz[k] = 1;
    if (tr[k].l)
    {
        dfs(tr[k].l);
        siz[k] += siz[tr[k].l];
        f[k] = (ll)f[k] * f[tr[k].l] % mod;
    }
    if (tr[k].r)
    {
        dfs(tr[k].r);
        siz[k] += siz[tr[k].r];
        f[k] = (ll)f[k] * f[tr[k].r] % mod;
    }
    f[k] = (ll)f[k] * c[siz[k] - 1][siz[tr[k].l]] % mod;
    return;
}
int main()
{
    c[0][0] = 1;
    for (int i = 1; i <= 1000; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= 1000; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    int m;
    scanf("%d", &m);
    while (m--)
    {
        rt = 0;
        cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            int x;
            scanf("%d", &x);
            insert(x);
        }
        dfs(1);
        printf("%d\n", (f[1] - 1 + mod) % mod);
    }
    return 0;
}