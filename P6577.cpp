#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
#define inf 0x7fffffffffffffff
int n, m, sum;
int head[505], mx[505], my[505];
int s[505], t[505], slack[505];
int x[505], y[505], pre[505];
int l[250005];
struct node
{
    int v;
    int w;
    int nxt;
} a[500005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void mch(int k)
{
    while (k)
    {
        int tmp = mx[pre[k]];
        mx[pre[k]] = k;
        my[k] = pre[k];
        k = tmp;
    }
    return;
}
void bfs(int k)
{
    int hh = 0, tt = 1;
    l[1] = k;
    while (1)
    {
        while (hh < tt)
        {
            k = l[++hh];
            s[k] = 1;
            int d = head[k];
            while (d)
            {
                if (!t[a[d].v])
                {
                    int p = x[k] + y[a[d].v] - a[d].w;
                    if (p < slack[a[d].v])
                        pre[a[d].v] = k;
                    if (!p)
                    {
                        t[a[d].v] = 1;
                        if (!my[a[d].v])
                        {
                            mch(a[d].v);
                            return;
                        }
                        else
                            l[++tt] = my[a[d].v];
                    }
                    else
                        slack[a[d].v] = min(slack[a[d].v], p);
                }
                d = a[d].nxt;
            }
        }
        int p = inf;
        for (int i = 1; i <= n; ++i)
            if (!t[i])
                p = min(p, slack[i]);
        for (int i = 1; i <= n; ++i)
        {
            if (s[i])
                x[i] -= p;
            if (t[i])
                y[i] += p;
            else
                slack[i] -= p;
        }
        for (int i = 1; i <= n; ++i)
            if (!t[i] && !slack[i])
            {
                t[i] = 1;
                if (!my[i])
                {
                    mch(i);
                    return;
                }
                else
                    l[++tt] = my[i];
            }
    }
    return;
}
void km()
{
    for (int i = 1; i <= n; ++i)
    {
        int d = head[i];
        while (d)
        {
            x[i] = max(x[i], a[d].w);
            d = a[d].nxt;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
        memset(slack, 0x7f, sizeof(slack));
        bfs(i);
    }
    return;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        ins(u, v, w);
    }
    km();
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += x[i] + y[i];
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", my[i]);
    return 0;
}