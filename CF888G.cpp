#include <iostream>
#include <cstdio>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
typedef long long ll;
int n, cnt, a[200005], l[6000005], r[6000005], tr[6000005][2];
void ins(int k)
{
    int rt = 0;
    for (int i = 29; i >= 0; --i)
    {
        int c = (a[k] & (1 << i)) != 0;
        if (!tr[rt][c])
        {
            tr[rt][c] = ++cnt;
            l[cnt] = k;
        }
        rt = tr[rt][c];
        r[rt] = k;
    }
    return;
}
int query(int k, int w)
{
    int rt = 0, num = 0;
    for (int i = 29; i >= 0; --i)
    {
        int c = (k & (1 << i)) != 0;
        if (tr[rt][c] && rt != w)
            rt = tr[rt][c];
        else
        {
            num += (1 << i);
            rt = tr[rt][c ^ 1];
        }
    }
    return num;
}
ll dfs(int k)
{
    ll ans = 0;
    if (tr[k][0])
        ans += dfs(tr[k][0]);
    if (tr[k][1])
        ans += dfs(tr[k][1]);
    if (tr[k][0] && tr[k][1])
    {
        int tmp = inf;
        for (int i = l[tr[k][0]]; i <= r[tr[k][0]]; ++i)
            tmp = min(tmp, query(a[i], k));
        ans += tmp;
    }
    return ans;
}
signed main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        ins(i);
    printf("%lld", dfs(0));
    return 0;
}