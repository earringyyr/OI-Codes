#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define inf 0x7fffffff
int n, m, sum;
int head[505], mx[505], my[505];
int s[505], t[505], slack[505];
int x[505], y[505], pre[505], pr[505];
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
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
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
int main()
{
    scanf("%d", &n);
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
    {
        ans += x[i] + y[i];
        pr[i] = mx[i];
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
    {
        int d = head[i];
        while (d)
        {
            if (a[d].v == pr[i])
            {
                int tmp = a[d].w, num = 0;
                a[d].w = 0;
                km();
                for (int j = 1; j <= n; ++j)
                    num += x[j] + y[j];
                a[d].w = tmp;
                if (num != ans)
                    printf("%d %d\n", i, pr[i]);
                break;
            }
            d = a[d].nxt;
        }
    }
    return 0;
}