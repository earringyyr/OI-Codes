#include <iostream>
#include <cstdio>
using namespace std;
int v, n, sum, num;
int head[105], dep[105];
struct node
{
    int v;
    int nxt;
} a[205];
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
    num = max(num, dep[k]);
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
    return;
}
int main()
{
    scanf("%d%d", &v, &n);
    for (int i = 1; i < v; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs(0, 0);
    if (num >= n)
        printf("%d", n + 1);
    else
        printf("%d", min(num + (n - num) / 2 + 1, v));
    return 0;
}