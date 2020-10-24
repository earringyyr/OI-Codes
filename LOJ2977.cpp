#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, k, sum, len, ans;
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
int A[255][255], c[255][255], w[255][255], f[255][255];
int head[255], vis[255], W[255], col[255], val[255];
struct edge
{
    int v;
    int nxt;
} a[1005];
struct node
{
    int id;
    int dis;
    node(int aa = 0, int bb = 0)
    {
        id = aa;
        dis = bb;
    }
    bool operator<(const node &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<node> q;
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra(int S)
{
    memset(vis, 0, sizeof(vis));
    while (!q.empty())
    {
        int k = q.top().id;
        q.pop();
        if (vis[k])
            continue;
        vis[k] = 1;
        int d = head[k];
        while (d)
        {
            if (!vis[a[d].v] && f[a[d].v][S] > f[k][S] + W[a[d].v])
            {
                f[a[d].v][S] = f[k][S] + W[a[d].v];
                q.push(node(a[d].v, f[a[d].v][S]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int calc()
{
    int num = inf;
    for (int T = 1; T <= 200; ++T)
    {
        memset(f, 0x3f, sizeof(f));
        for (int i = 1; i <= len; ++i)
            col[i] = rand() % k + 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (c[i][j] != -1)
                    f[(i - 1) * m + j][1 << (col[c[i][j]] - 1)] = w[i][j];
        for (int S = 1; S < (1 << k); ++S)
        {
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j)
                    if (c[i][j] != -1)
                    {
                        for (int s = S & (S - 1); s; s = (s - 1) & S)
                            f[(i - 1) * m + j][S] = min(f[(i - 1) * m + j][S], f[(i - 1) * m + j][s] + f[(i - 1) * m + j][S ^ s] - w[i][j]);
                        if (f[(i - 1) * m + j][S] != inf)
                            q.push(node((i - 1) * m + j, f[(i - 1) * m + j][S]));
                    }
            dijkstra(S);
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                num = min(num, f[(i - 1) * m + j][(1 << k) - 1]);
    }
    return num;
}
int main()
{
    srand(time(0));
    int T;
    scanf("%d", &T);
    while (T--)
    {
        len = 0;
        sum = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &c[i][j]);
                if (c[i][j] != -1)
                    col[++len] = c[i][j];
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &A[i][j]);
                val[(i - 1) * m + j] = A[i][j];
            }
        sort(col + 1, col + len + 1);
        len = unique(col + 1, col + len + 1) - col - 1;
        if (len < k)
        {
            puts("-1 -1");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (c[i][j] != -1)
                    c[i][j] = lower_bound(col + 1, col + len + 1, c[i][j]) - col;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 0; k < 4; ++k)
                {
                    int x = i + gox[k], y = j + goy[k];
                    if (x >= 1 && x <= n && y >= 1 && y <= m && c[x][y] != -1)
                        ins((i - 1) * m + j, (x - 1) * m + y);
                }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                w[i][j] = 1;
                W[(i - 1) * m + j] = 1;
            }
        ans = calc();
        printf("%d ", ans);
        sort(val + 1, val + n * m + 1);
        int num = unique(val + 1, val + n * m + 1) - val - 1;
        int lef = 1, rig = num;
        while (lef < rig)
        {
            int mid = (lef + rig) >> 1;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j)
                    if (A[i][j] <= val[mid])
                    {
                        w[i][j] = 9999;
                        W[(i - 1) * m + j] = 9999;
                    }
                    else
                    {
                        w[i][j] = 10001;
                        W[(i - 1) * m + j] = 10001;
                    }
            if (calc() <= 9999 * ans + 2 * (ans - ((ans + 1) / 2)))
                rig = mid;
            else
                lef = mid + 1;
        }
        printf("%d\n", val[lef]);
    }
    return 0;
}