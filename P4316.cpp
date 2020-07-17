#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum;
int head[100005], siz[100005];
double f[100005];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    if (f[k] != -1)
        return;
    f[k] = 0;
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        f[k] += 1.0 / siz[k] * (f[a[d].v] + a[d].w);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ++siz[u];
    }
    for (int i = 1; i < n; ++i)
        f[i] = -1;
    f[n] = 0;
    dfs(1);
    printf("%.2f", f[1]);
    return 0;
}