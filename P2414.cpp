#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int m, len, rt, cnt, num, h, t, sum, tot, ssum;
int fa[100005], bo[100005], l[100005], nxt[100005], head[100005], hhead[100005];
int st[100005], en[100005], c[100005], ans[100005];
int tr[100005][26];
char s[100005];
struct node
{
    int v;
    int nxt;
} a[100005], b[100005];
struct point
{
    int id;
    int x;
    point(int aa = 0, int bb = 0)
    {
        id = aa;
        x = bb;
    }
};
vector<point> q[100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void iins(int u, int v)
{
    ++ssum;
    b[ssum].v = v;
    b[ssum].nxt = hhead[u];
    hhead[u] = ssum;
    return;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= tot)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
void dfs(int k, int fa)
{
    st[k] = ++tot;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs(a[d].v, k);
        d = a[d].nxt;
    }
    en[k] = tot;
    return;
}
void solve(int k, int fa)
{
    add(st[k], 1);
    int siz = q[k].size();
    for (int i = 0; i < siz; ++i)
        ans[q[k][i].id] = ask(en[q[k][i].x]) - ask(st[q[k][i].x] - 1);
    int d = hhead[k];
    while (d)
    {
        if (b[d].v != fa)
            solve(b[d].v, k);
        d = b[d].nxt;
    }
    add(st[k], -1);
    return;
}
int main()
{
    scanf("%s", s + 1);
    len = strlen(s + 1);
    for (int i = 1; i <= len; ++i)
        if (s[i] == 'B')
            rt = fa[rt];
        else if (s[i] == 'P')
            bo[++num] = rt;
        else
        {
            int k = s[i] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            iins(rt, tr[rt][k]);
            fa[tr[rt][k]] = rt;
            rt = tr[rt][k];
        }
    for (int i = 0; i < 26; ++i)
        if (tr[0][i])
            l[++t] = tr[0][i];
    while (h < t)
    {
        ++h;
        rt = l[h];
        for (int i = 0; i < 26; ++i)
            if (!tr[rt][i])
                tr[rt][i] = tr[nxt[rt]][i];
            else
            {
                nxt[tr[rt][i]] = tr[nxt[rt]][i];
                l[++t] = tr[rt][i];
            }
    }
    for (int i = 1; i <= cnt; ++i)
        ins(nxt[i], i);
    dfs(0, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        q[bo[y]].push_back(point(i, bo[x]));
    }
    solve(0, 0);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}