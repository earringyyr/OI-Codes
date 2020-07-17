#include <iostream>
#include <cstdio>
using namespace std;
int n, sum, h, t, ans, head[10005], in[10005], ti[10005], vis[10005], q[10005];
struct node
{
    int v;
    int nxt;
} a[100000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int gu;
        scanf("%d", &gu);
        scanf("%d", &ti[i]);
        int v;
        while (scanf("%d", &v))
        {
            if (!v)
                break;
            ins(v, i);
            ++in[i];
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!in[i])
            q[++t] = i;
    while (h < t)
    {
        int k = q[++h];
        int d = head[k];
        while (d)
        {
            --in[a[d].v];
            if (!in[a[d].v])
                q[++t] = a[d].v;
            vis[a[d].v] = max(vis[a[d].v], ti[k] + vis[k]);
            d = a[d].nxt;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (ti[i] + vis[i] > ans)
            ans = ti[i] + vis[i];
    printf("%d", ans);
    return 0;
}