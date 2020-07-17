#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct node
{
    int v;
    int nxt;
} a[200005];
struct pi
{
    int id;
    int sid;
    int dis;
    pi(int aa = 0, int bb = 0, int cc = 0)
    {
        id = aa;
        sid = bb;
        dis = cc;
    }
    bool operator<(const pi &bb) const
    {
        return dis > bb.dis;
    }
};
priority_queue<pi> q;
int n, m, qq, sum, head[100005], dis[100005][2], vis[100005][2];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dijkstra()
{
    memset(dis, 0x7f, sizeof(dis));
    dis[1][0] = 0;
    q.push(pi(1, 0, 0));
    while (!q.empty())
    {
        int id = q.top().id, sid = q.top().sid;
        q.pop();
        if (vis[id][sid])
            continue;
        vis[id][sid] = 1;
        int d = head[id];
        while (d)
        {
            if (!vis[a[d].v][sid ^ 1] && dis[id][sid] + 1 < dis[a[d].v][sid ^ 1])
            {
                dis[a[d].v][sid ^ 1] = dis[id][sid] + 1;
                q.push(pi(a[d].v, sid ^ 1, dis[a[d].v][sid ^ 1]));
            }
            d = a[d].nxt;
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &qq);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dijkstra();
    for (int i = 1; i <= qq; ++i)
    {
        int a, l;
        scanf("%d%d", &a, &l);
        if (l % 2 == 0 && dis[a][0] <= l)
            puts("Yes");
        else if (l % 2 == 1 && dis[a][1] <= l)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}