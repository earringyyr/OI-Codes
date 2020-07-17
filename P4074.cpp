#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, qq, sum, cnt, num, tot, len;
long long ans[100005];
int dep[100005], v[100005];
int gu[100005], vis[100005];
int w[100005], c[100005], cc[100005];
int head[100005], in[100005], out[100005];
int siz[100005], son[100005], ll[200005];
int fa[100005], top[100005], q[100005][3];
struct node
{
    int v;
    int nxt;
} a[200005];
struct point
{
    int id;
    int x;
    int y;
    int lca;
    int z;
} b[100005];
bool cmp(point aa, point bb)
{
    if ((aa.x - 1) / len == (bb.x - 1) / len)
    {
        if ((aa.y + 1) / len == (bb.y - 1) / len)
            return aa.z < bb.z;
        return aa.y < bb.y;
    }
    return aa.x < bb.x;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    in[k] = ++cnt;
    ll[cnt] = k;
    son[k] = -1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k])
        {
            fa[a[d].v] = k;
            dep[a[d].v] = dep[k] + 1;
            dfs1(a[d].v);
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
            siz[k] += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    out[k] = ++cnt;
    ll[cnt] = k;
    return;
}
void dfs2(int k, int topf)
{
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}
void del(int x)
{
    ans[0] -= (long long)v[c[x]] * w[gu[c[x]]];
    --gu[c[x]];
    return;
}
void add(int x)
{
    ++gu[c[x]];
    ans[0] += (long long)v[c[x]] * w[gu[c[x]]];
    return;
}
void move(int x)
{
    if (vis[x])
        del(x);
    else
        add(x);
    vis[x] ^= 1;
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &qq);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &v[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1);
    dfs2(1, 1);
    len = pow(cnt, 2.0 / 3.0);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
        cc[i] = c[i];
    }
    for (int i = 1; i <= qq; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 0)
        {
            ++tot;
            scanf("%d%d", &q[tot][0], &q[tot][1]);
            q[tot][2] = cc[q[tot][0]];
            cc[q[tot][0]] = q[tot][1];
        }
        else
        {
            ++num;
            b[num].id = num;
            scanf("%d%d", &b[num].x, &b[num].y);
            if (dep[b[num].x] > dep[b[num].y])
                swap(b[num].x, b[num].y);
            if (b[num].x == lca(b[num].x, b[num].y))
            {
                b[num].x = in[b[num].x];
                b[num].y = in[b[num].y];
            }
            else
            {
                b[num].lca = lca(b[num].x, b[num].y);
                b[num].x = out[b[num].x];
                b[num].y = in[b[num].y];
            }
            b[num].z = tot;
        }
    }
    sort(b + 1, b + num + 1, cmp);
    int x = 1, y = 0, z = 0;
    for (int i = 1; i <= num; ++i)
    {
        while (x < b[i].x)
            move(ll[x++]);
        while (x > b[i].x)
            move(ll[--x]);
        while (y < b[i].y)
            move(ll[++y]);
        while (y > b[i].y)
            move(ll[y--]);
        while (z < b[i].z)
        {
            ++z;
            bool p = false;
            if (vis[q[z][0]])
                p = true;
            if (p)
                move(q[z][0]);
            c[q[z][0]] = q[z][1];
            if (p)
                move(q[z][0]);
        }
        while (z > b[i].z)
        {
            bool p = false;
            if (vis[q[z][0]])
                p = true;
            if (p)
                move(q[z][0]);
            c[q[z][0]] = q[z][2];
            if (p)
                move(q[z][0]);
            --z;
        }
        if (b[i].lca)
            move(b[i].lca);
        ans[b[i].id] = ans[0];
        if (b[i].lca)
            move(b[i].lca);
    }
    for (int i = 1; i <= num; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}