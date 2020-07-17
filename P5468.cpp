#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
int n, m, A, B, C, ans = 0x7fffffff;
int top[100005], pos[100005];
struct node
{
    int x;
    int y;
    int p;
    int q;
} a[200005];
struct point
{
    int x;
    int y;
    point(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
    bool operator<(const point &bb) const
    {
        return x > bb.x;
    }
    point operator-(const point &bb) const
    {
        return point(x - bb.x, y - bb.y);
    }
    int operator^(const point &bb) const
    {
        return x * bb.y - y * bb.x;
    }
};
vector<point> st[100005];
priority_queue<point> q[100005];
bool cmp(node aa, node bb)
{
    return aa.p < bb.p;
}
int main()
{
    scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].p, &a[i].q);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        pos[i] = 1;
        st[i].push_back(0);
    }
    q[1].push(point(0, 0));
    for (int i = 1; i <= m; ++i)
    {
        while (!q[a[i].x].empty() && q[a[i].x].top().x <= a[i].p)
        {
            while (top[a[i].x] > 1 && ((st[a[i].x][top[a[i].x]] - q[a[i].x].top()) ^ (st[a[i].x][top[a[i].x] - 1] - q[a[i].x].top())) >= 0)
            {
                --top[a[i].x];
                st[a[i].x].pop_back();
                if (pos[a[i].x] > top[a[i].x])
                    --pos[a[i].x];
            }
            ++top[a[i].x];
            st[a[i].x].push_back(q[a[i].x].top());
            q[a[i].x].pop();
        }
        if (!top[a[i].x])
            continue;
        point now(1, 2 * A * a[i].p);
        while (pos[a[i].x] < top[a[i].x] && ((st[a[i].x][pos[a[i].x] + 1] - st[a[i].x][pos[a[i].x]]) ^ now) > 0)
            ++pos[a[i].x];
        int num = st[a[i].x][pos[a[i].x]].y - 2 * A * a[i].p * st[a[i].x][pos[a[i].x]].x + A * a[i].p * a[i].p + B * a[i].p + C;
        q[a[i].y].push(point(a[i].q, num + A * a[i].q * a[i].q - B * a[i].q));
        if (a[i].y == n)
            ans = min(ans, num + a[i].q);
    }
    printf("%d", ans);
    return 0;
}