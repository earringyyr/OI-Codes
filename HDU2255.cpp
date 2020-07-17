#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define inf 0x7f7f7f7f
int n, sum, head[305], mch[305], s[305], t[305], slack[305], x[305], y[305];
struct node
{
    int v;
    int w;
    int next;
} a[90005];
inline void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
inline bool dfs(int k, int cnt)
{
    s[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (t[a[d].v] == cnt)
        {
            d = a[d].next;
            continue;
        }
        int p = x[k] + y[a[d].v] - a[d].w;
        if (!p)
        {
            t[a[d].v] = cnt;
            if (!mch[a[d].v] || dfs(mch[a[d].v], cnt))
            {
                mch[a[d].v] = k;
                return true;
            }
        }
        else
            slack[a[d].v] = min(slack[a[d].v], p);
        d = a[d].next;
    }
    return false;
}
inline void update(int cnt)
{
    int p = inf;
    for (int i = 1; i <= n; ++i)
        if (t[i] != cnt)
            p = min(p, slack[i]);
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == cnt)
            x[i] -= p;
        if (t[i] == cnt)
            y[i] += p;
    }
    return;
}
inline void km()
{
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(mch, 0, sizeof(mch));
    for (int i = 1; i <= n; ++i)
    {
        int d = head[i];
        while (d)
        {
            x[i] = max(x[i], a[d].w);
            d = a[d].next;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
        memset(slack, 0x7f, sizeof(slack));
        int cnt = 0;
        while (!dfs(i, ++cnt))
            update(cnt);
    }
    return;
}
int main()
{
    while (scanf("%d", &n) == 1)
    {
        sum = 0;
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                int w;
                scanf("%d", &w);
                ins(i, j, w);
            }
        km();
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            ans += x[i] + y[i];
        printf("%d\n", ans);
    }
    return 0;
}