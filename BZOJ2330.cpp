#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, k, sum, h, t;
int head[100005], d[100005];
int vis[100005], q[100005], s[100005];
long long ans;
struct node
{
    int v;
    int w;
    int next;
} a[300005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void spfa()
{
    h = 0;
    t = 1;
    q[1] = 0;
    s[0] = 1;
    while (h < t)
    {
        h++;
        int k = q[h];
        vis[k]++;
        if (vis[k] == n)
        {
            puts("-1");
            exit(0);
        }
        s[k] = 0;
        int l = head[k];
        while (l)
        {
            if (d[a[l].v] < d[k] + a[l].w)
            {
                d[a[l].v] = d[k] + a[l].w;
                if (!s[a[l].v])
                {
                    q[++t] = a[l].v;
                    s[a[l].v] = 1;
                }
            }
            l = a[l].next;
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i)
    {
        int x, aa, bb;
        scanf("%d%d%d", &x, &aa, &bb);
        switch (x)
        {
        case 1:
            ins(aa, bb, 0);
            ins(bb, aa, 0);
            break;
        case 2:
            ins(aa, bb, 1);
            break;
        case 3:
            ins(bb, aa, 0);
            break;
        case 4:
            ins(bb, aa, 1);
            break;
        case 5:
            ins(aa, bb, 0);
            break;
        }
    }
    for (int i = n; i >= 1; --i)
        ins(0, i, 1);
    spfa();
    for (int i = 1; i <= n; ++i)
        ans += d[i];
    printf("%lld", ans);
    return 0;
}