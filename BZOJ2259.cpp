#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int n, sum, dis[1000005], vis[1000005];
int pre[1000005], nxt[1000005];
int A[1000005], head[1000005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[4000005];
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
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(dis, 0x7f, sizeof(dis));
    q.push(node(1, 0));
    dis[1] = 0;
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
            if (!vis[a[d].v] && dis[a[d].v] > dis[k] + a[d].w)
            {
                dis[a[d].v] = dis[k] + a[d].w;
                q.push(node(a[d].v, dis[a[d].v]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
        for (int j = min(i + A[i] + 1, n + 1); j > 1 && !pre[j]; --j)
        {
            pre[j] = 1;
            ins(j, j - 1, 1);
        }
        for (int j = i + A[i] + 1; j <= n && !nxt[j]; ++j)
        {
            nxt[j] = 1;
            ins(j, j + 1, 1);
        }
        if (i + A[i] <= n)
            ins(i, i + A[i] + 1, 0);
        else
            ins(i, n + 1, i + A[i] - n);
    }
    dijkstra();
    printf("%d", dis[n + 1]);
    return 0;
}