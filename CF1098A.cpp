#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
int n, sum;
int fa[100005], s[100005], head[100005], dep[100005];
ll ans;
struct node
{
    int v;
    int nxt;
} a[100005];
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
    if (dep[k] % 2 == 0)
    {
        s[k] = s[fa[k]];
        int tmp = 2e9;
        int d = head[k];
        if (!d)
            return;
        while (d)
        {
            tmp = min(tmp, s[a[d].v]);
            d = a[d].nxt;
        }
        if (tmp < s[fa[k]])
        {
            printf("-1");
            exit(0);
        }
        s[k] = tmp;
        ans += s[k] - s[fa[k]];
    }
    else
    {
        if (s[k] < 0)
        {
            printf("-1");
            exit(0);
        }
        if (s[k] < s[fa[k]])
        {
            printf("-1");
            exit(0);
        }
        ans += s[k] - s[fa[k]];
    }
    int d = head[k];
    while (d)
    {
        dep[a[d].v] = dep[k] + 1;
        dfs(a[d].v);
        d = a[d].nxt;
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &fa[i]);
        ins(fa[i], i);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &s[i]);
    dep[1] = 1;
    dfs(1);
    printf("%lld", ans);
    return 0;
}