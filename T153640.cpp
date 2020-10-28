#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, q, sum, num = 1;
int head[200005], w[200005];
int dep[200005], val[400005];
struct node
{
    int v;
    int nxt;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    val[dep[k]] ^= w[k];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    dfs(1, 0);
    while (num < n)
        num <<= 1;
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
                val[j + mid + k] = val[j + k] ^ val[j + mid + k];
    for (int i = 1; i <= q; ++i)
    {
        int t;
        scanf("%d", &t);
        if (!t)
            printf("%d\n", w[1]);
        else
            printf("%d\n", val[num - 1 - ((t - 1) % num)]);
    }
    return 0;
}