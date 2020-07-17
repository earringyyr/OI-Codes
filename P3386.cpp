#include <iostream>
#include <cstdio>
using namespace std;
int n, m, e, sum, ans;
int vis[1005], mch[1005], head[1005];
struct node
{
    int v;
    int next;
} a[1000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k, int t)
{
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v] != t)
        {
            vis[a[d].v] = t;
            if (!mch[a[d].v] || dfs(mch[a[d].v], t))
            {
                mch[a[d].v] = k;
                return true;
            }
        }
        d = a[d].next;
    }
    return false;
}
void doit()
{
    for (int i = 1; i <= n; ++i)
        if (dfs(i, i))
            ++ans;
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= e; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (v > m || u > n)
            continue;
        ins(u, v);
    }
    doit();
    printf("%d", ans);
    return 0;
}