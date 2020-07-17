#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, h, t;
int q[100005], cnt[100005], head[100005], f[100005];
struct node
{
    int v;
    int next;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        cnt[y]++;
    }
    for (int i = 1; i <= n; ++i)
        if (!cnt[i])
        {
            f[i] = 1;
            q[++t] = i;
        }
    while (h < t)
    {
        h++;
        int d = head[q[h]];
        while (d)
        {
            cnt[a[d].v]--;
            if (cnt[a[d].v] == 0)
                q[++t] = a[d].v;
            d = a[d].next;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int d = head[q[i]];
        while (d)
        {
            f[a[d].v] = max(f[a[d].v], f[q[i]] + 1);
            d = a[d].next;
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", f[i]);
    return 0;
}