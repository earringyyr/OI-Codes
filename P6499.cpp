#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, K, sum, cnt, ans;
int head[405], dep[405];
int st[405], ed[405];
int f[1000005][405];
struct node
{
    int v;
    int nxt;
} a[805];
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
    st[k] = cnt + 1;
    if (dep[k] == K)
    {
        ++cnt;
        st[k] = cnt;
        ed[k] = cnt;
        return;
    }
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
    ed[k] = cnt;
    return;
}
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    if (n <= K * K + 1)
    {
        printf("DA");
        return 0;
    }
    dfs(1, 0);
    if (!cnt)
    {
        printf("DA");
        return 0;
    }
    f[0][0] = 1;
    for (int i = 1; i < (1 << K); ++i)
    {
        for (int j = 1; j <= n; ++j)
            if (dep[j] >= 1 && dep[j] <= K && (i & (1 << (dep[j] - 1))))
                f[i][ed[j]] |= f[i - (1 << (dep[j] - 1))][st[j] - 1];
        ans |= f[i][cnt];
    }
    if (ans)
        printf("DA");
    else
        printf("NE");
    return 0;
}