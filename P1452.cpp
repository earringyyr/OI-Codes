#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n, top, ans, st[50005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    int operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
    int dis(const node &bb) const
    {
        return (x - bb.x) * (x - bb.x) + (y - bb.y) * (y - bb.y);
    }
} p[50005];
bool cmp1(node aa, node bb)
{
    if (aa.y == bb.y)
        return aa.x < bb.x;
    return aa.y < bb.y;
}
bool cmp2(node aa, node bb)
{
    if (((aa - p[1]) ^ (bb - p[1])) == 0)
        return aa.dis(p[1]) < bb.dis(p[1]);
    return ((aa - p[1]) ^ (bb - p[1])) < 0;
}
bool check(node aa, node bb, node cc, node dd)
{
    int sa, sb;
    sa = abs((bb - aa) ^ (cc - aa));
    sb = abs((bb - aa) ^ (dd - aa));
    return sa < sb;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp1);
    sort(p + 2, p + n + 1, cmp2);
    for (int i = 1; i <= n; ++i)
    {
        while (top > 1 && ((p[st[top]] - p[i]) ^ (p[st[top - 1]] - p[i])) <= 0)
            --top;
        st[++top] = i;
    }
    st[top + 1] = st[1];
    int j = 2;
    for (int i = 1; i <= top; ++i)
    {
        while (j != i && check(p[st[i]], p[st[i + 1]], p[st[j]], p[st[j + 1]]))
        {
            j = (j + 1) % top;
            if (j == 0)
                j = top;
        }
        ans = max(ans, p[st[i]].dis(p[st[j]]));
    }
    printf("%d", ans);
    return 0;
}