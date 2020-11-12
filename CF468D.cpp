#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
typedef long long ll;
int n, sum, rt, cnt;
int head[100005], siz[100005], f[100005];
int id[100005], in[100005], out[100005];
ll ans;
set<int> s[100005];
set<pii> minx, maxn;
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
void dfs1(int k, int fa)
{
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = max(f[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    f[k] = max(f[k], n - siz[k]);
    if (f[k] < f[rt])
        rt = k;
    return;
}
void dfs2(int k, int fa, ll dep)
{
    siz[k] = 1;
    ans += dep;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs2(a[d].v, k, dep + a[d].w);
            siz[k] += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
void dfs3(int k, int fa)
{
    id[k] = cnt;
    s[cnt].insert(k);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs3(a[d].v, k);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    f[0] = n;
    dfs1(1, 0);
    dfs2(rt, 0, 0);
    printf("%lld\n", ans * 2);
    cnt = 1;
    id[rt] = cnt;
    s[cnt].insert(rt);
    in[cnt] = 1;
    out[cnt] = 1;
    minx.insert(mp(rt, cnt));
    maxn.insert(mp(-2, cnt));
    // cout << rt << endl;
    int d = head[rt];
    while (d)
    {
        ++cnt;
        in[cnt] = siz[a[d].v];
        out[cnt] = siz[a[d].v];
        dfs3(a[d].v, rt);
        minx.insert(mp(*s[cnt].begin(), cnt));
        maxn.insert(mp(-(in[cnt] + out[cnt]), cnt));
        d = a[d].nxt;
    }
    for (int i = 1; i <= n; ++i)
    {
        maxn.erase(maxn.find(mp(-(in[id[i]] + out[id[i]]), id[i])));
        --in[id[i]];
        maxn.insert(mp(-(in[id[i]] + out[id[i]]), id[i]));
        pii top = *maxn.begin();
        if (top.second != 1 && -top.first == n - i + 1)
        {
            int id = top.second;
            printf("%d ", *s[id].begin());
            --out[id];
            maxn.erase(maxn.begin());
            maxn.insert(mp(-(in[id] + out[id]), id));
            minx.erase(minx.find(mp(*s[id].begin(), id)));
            s[id].erase(s[id].begin());
            if (!s[id].empty())
                minx.insert(mp(*s[id].begin(), id));
        }
        else
        {
            set<pii>::iterator k = minx.begin();
            if (i != rt && (*k).second == id[i])
                ++k;
            printf("%d ", (*k).first);
            maxn.erase(maxn.find(mp(-(in[(*k).second] + out[(*k).second]), (*k).second)));
            --out[(*k).second];
            maxn.insert(mp(-(in[(*k).second] + out[(*k).second]), (*k).second));
            s[(*k).second].erase(s[(*k).second].begin());
            if (!s[(*k).second].empty())
                minx.insert(mp(*s[(*k).second].begin(), (*k).second));
            minx.erase(k);
        }
    }
    return 0;
}