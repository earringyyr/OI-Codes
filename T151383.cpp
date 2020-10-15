#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, sum, head[300005], vis[300005], num[300005];
ll ans;
struct node
{
    int v;
    int nxt;
} a[300005];
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
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
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
            dfs(a[d].v);
        ans += (ll)num[k] * (num[a[d].v] + 1);
        num[k] += num[a[d].v] + 1;
        d = a[d].nxt;
    }
    return;
}
int main()
{
    n = read();
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        u = read();
        v = read();
        if (u < v)
            swap(u, v);
        ins(u, v);
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i);
    ans *= 2;
    printf("%lld", ans);
    return 0;
}