#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
int n, seed = 2333, in[100005];
unordered_map<unsigned int, int> mp;
struct tree
{
    int sum, top, cnt;
    int head[100005], siz[100005], st[100005];
    unsigned int f[100005], g[100005];
    struct node
    {
        int v;
        int nxt;
    } a[200005];
    bool cmp(int aa, int bb)
    {
        return f[aa] < f[bb];
    }
    void ins(int u, int v)
    {
        ++sum;
        a[sum].v = v;
        a[sum].nxt = head[u];
        head[u] = sum;
        return;
    }
    void dfs1(int k, int fa)
    {
        f[k] = 0;
        siz[k] = 1;
        int d = head[k];
        while (d)
        {
            if (a[d].v != fa)
            {
                dfs1(a[d].v, k);
                siz[k] += siz[a[d].v];
                f[k] ^= f[a[d].v] * seed;
            }
            d = a[d].nxt;
        }
        f[k] += siz[k];
        return;
    }
    void dfs2(int k, int fa)
    {
        if (k != 1)
            g[k] = ((g[fa] * seed) ^ (f[fa] - siz[fa]) ^ (f[k] * seed)) + cnt - siz[k];
        if (cnt == n)
            ++mp[((f[k] - siz[k]) ^ (g[k] * seed)) + cnt];
        int d = head[k];
        while (d)
        {
            if (a[d].v != fa)
                dfs2(a[d].v, k);
            d = a[d].nxt;
        }
        return;
    }
} T1, T2;
int main()
{
    scanf("%d", &n);
    T1.cnt = n;
    T2.cnt = n + 1;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        T1.ins(u, v);
        T1.ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++in[u];
        ++in[v];
        T2.ins(u, v);
        T2.ins(v, u);
    }
    T1.dfs1(1, 0);
    T1.dfs2(1, 0);
    T2.dfs1(1, 0);
    T2.dfs2(1, 0);
    for (int i = 1; i <= n + 1; ++i)
        if (in[i] == 1)
        {
            int d = T2.a[T2.head[i]].v;
            if (mp[T2.f[d]] || mp[T2.g[i]])
            {
                printf("%d", i);
                return 0;
            }
        }
    return 0;
}