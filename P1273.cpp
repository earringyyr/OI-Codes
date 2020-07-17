#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum, ans, head[3005], f[3005][3005], siz[3005];
struct node
{
    int v;
    int next;
    int w;
} a[3005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    int d = head[k];
    while (d)
    {
        dfs1(a[d].v);
        siz[k] += siz[a[d].v];
        d = a[d].next;
    }
    return;
}
void dfs2(int k)
{
    f[k][0]=0;
    int d = head[k];
    while (d)
    {
        dfs2(a[d].v);
        for (int i = siz[k]; i >= 0; --i)
            for (int j = 0; j <= min(siz[a[d].v], i); ++j)
                f[k][i] = max(f[k][i], f[a[d].v][j] + f[k][i - j] - a[d].w);
        d = a[d].next;
    }
    return;
}
int main()
{
    for(int i=0;i<3005;++i)
        siz[i]=1;
    memset(f,-0x3f3f3f,sizeof(f));
    cin >> n >> m;
    for (int i = 1; i <= n - m; ++i)
    {
        int k;
        cin >> k;
        for (int j = 1; j <= k; ++j)
        {
            int aa, c;
            cin >> aa >> c;
            ins(i, aa, c);
        }
    }
    for (int i = n - m + 1; i <= n; ++i)
        cin >> f[i][1];
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= siz[1]; ++i)
        if (f[1][i] >= 0)
            ans = i;
    cout << ans;
    return 0;
}