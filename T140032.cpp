#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, num, tot, cnt, mid, rt, sum, s, t, ans;
int len[305], head[100005], lev[100005], cur[100005], nxt[305][305][26], tr[100005][26];
char S[305][305];
struct node
{
    int v;
    int w;
    int nxt;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = 1;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
void dfs(int id, int k)
{
    ++tot;
    if (tot >= n + 1)
        return;
    if (num == mid)
        return;
    for (int i = 0; i < 26; ++i)
        if (nxt[id][k][i])
        {
            ++num;
            dfs(id, nxt[id][k][i]);
            --num;
        }
    return;
}
void link(int id, int k)
{
    if (num == mid)
        return;
    for (int i = 0; i < 26; ++i)
        if (nxt[id][k][i])
        {
            ++num;
            int tmp = rt;
            if (!tr[rt][i])
                tr[rt][i] = ++cnt;
            rt = tr[rt][i];
            ins(id, rt + n);
            link(id, nxt[id][k][i]);
            --num;
            rt = tmp;
        }
}
bool bfs()
{
    memset(lev, -1, sizeof(lev));
    memcpy(cur, head, sizeof(head));
    lev[s] = 0;
    int hh = 0, tt = 1, l[100005];
    l[tt] = s;
    while (hh < tt)
    {
        ++hh;
        int k = l[hh];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                l[++tt] = a[d].v;
            }
            d = a[d].nxt;
        }
    }
    return lev[t] != -1;
}
int dinic(int k, int flow)
{
    if (k == t)
        return flow;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (a[d].w > 0 && lev[a[d].v] == lev[k] + 1)
        {
            delta = dinic(a[d].v, min(a[d].w, flow - res));
            if (delta)
            {
                a[d].w -= delta;
                a[d ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        d = a[d].nxt;
        cur[k] = d;
    }
    if (res != flow)
        lev[k] = -1;
    return res;
}
bool check()
{
    cnt = 0;
    rt = 0;
    sum = 1;
    ans = 0;
    memset(head, 0, sizeof(head));
    memset(tr, 0, sizeof(tr));
    for (int i = 1; i <= n; ++i)
    {
        tot = 0;
        dfs(i, 0);
        if (tot <= n)
        {
            ++ans;
            link(i, 0);
        }
    }
    s = 0;
    t = cnt + n + 1;
    for (int i = 1; i <= n; ++i)
        ins(s, i);
    for (int i = 1; i <= cnt; ++i)
        ins(i + n, t);
    while (bfs())
        ans -= dinic(s, inf);
    return ans == 0;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", S[i] + 1);
        len[i] = strlen(S[i] + 1);
        len[0] = max(len[0], len[i]);
        int lst[26] = {0};
        for (int j = len[i]; j >= 0; --j)
        {
            for (int k = 0; k < 26; ++k)
                nxt[i][j][k] = lst[k];
            lst[S[i][j] - 'a'] = j;
        }
    }
    int l = 1, r = len[0] + 1;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (check())
            r = mid;
        else
            l = mid + 1;
    }
    if (l == len[0] + 1)
        printf("-1");
    else
        printf("%d", l);
    return 0;
}