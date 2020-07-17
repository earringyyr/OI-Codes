#include <iostream>
#include <cstdio>
#define inf 0x7fffffff
using namespace std;
int n, n1, n2, s, t, sum = 1, ans;
int head[70005], lev[70005], cur[70005], pos[50][50][4];
int num[50] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
struct card
{
    int x;
    int y;
    int z;
} c[60005];
struct node
{
    int u;
    int v;
    int w;
    int nxt;
} a[2000005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
bool bfs()
{
    int hhead = 0, ttail = 1, q[70005];
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
    }
    q[1] = s;
    lev[s] = 0;
    while (hhead < ttail)
    {
        ++hhead;
        int k = q[hhead];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                q[++ttail] = a[d].v;
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
        if (a[d].w > 0 && lev[k] + 1 == lev[a[d].v])
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
int main()
{
    scanf("%d%d", &n1, &n2);
    n = n1 + n2;
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].z);
    for (int i = 1; i <= 46; ++i)
        for (int j = 1; j <= 46; ++j)
            for (int k = 1; k <= 3; ++k)
                pos[i][j][k] = ++n;
    t = n + 1;
    n = n1 + n2;
    for (int i = 1; i <= n1; ++i)
    {
        ins(s, i, 1);
        for (int x = 1; x <= 46; ++x)
            for (int y = 1; y <= 46; ++y)
            {
                if (c[i].x % num[x] == 0 && c[i].y % num[y] == 0)
                    ins(i, pos[x][y][1], 1);
                if (c[i].y % num[x] == 0 && c[i].z % num[y] == 0)
                    ins(i, pos[x][y][2], 1);
                if (c[i].z % num[x] == 0 && c[i].x % num[y] == 0)
                    ins(i, pos[x][y][3], 1);
            }
    }
    for (int i = n1 + 1; i <= n; ++i)
    {
        ins(i, t, 1);
        for (int x = 1; x <= 46; ++x)
            for (int y = 1; y <= 46; ++y)
            {
                if (c[i].x % num[x] == 0 && c[i].y % num[y] == 0)
                    ins(pos[x][y][1], i, 1);
                if (c[i].y % num[x] == 0 && c[i].z % num[y] == 0)
                    ins(pos[x][y][2], i, 1);
                if (c[i].z % num[x] == 0 && c[i].x % num[y] == 0)
                    ins(pos[x][y][3], i, 1);
            }
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%d", ans);
    return 0;
}