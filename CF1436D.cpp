#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n, sum, head[200005], A[200005], num[200005];
ll maxn[200005], f[200005];
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    if (!head[k])
    {
        num[k] = 1;
        maxn[k] = A[k];
        return;
    }
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        num[k] += num[a[d].v];
        maxn[k] = max(maxn[k], maxn[a[d].v]);
        d = a[d].nxt;
    }
    d = head[k];
    while (d)
    {
        f[k] += f[a[d].v] + (maxn[k] - maxn[a[d].v]) * num[a[d].v];
        d = a[d].nxt;
    }
    if (A[k] <= f[k])
    {
        f[k] -= A[k];
        return;
    }
    A[k] -= f[k];
    maxn[k] += ceil((double)A[k] / num[k]);
    f[k] = ceil((double)A[k] / num[k]) * num[k] - A[k];
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        scanf("%d", &fa);
        ins(fa, i);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    dfs(1);
    printf("%lld", maxn[1]);
    return 0;
}