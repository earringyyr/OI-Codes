#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, id = 1, top;
int st[100005];
struct node
{
    ll x;
    ll y;
    node(ll xx = 0, ll yy = 0)
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
    ll operator^(const node &bb) const
    {
        return (ll)x * bb.y - (ll)y * bb.x;
    }
    ll dis(node bb)
    {
        return bb.x - x;
    }
} p[100005];
bool cmp(node aa, node bb)
{
    ll tmp = (aa - p[1]) ^ (bb - p[1]);
    if (tmp)
        return tmp < 0;
    if ((aa - p[1]).x != (bb - p[1]).x)
        return (aa - p[1]).x < (bb - p[1]).x;
    return (aa - p[1]).y < (bb - p[1]).y;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        p[i].y = p[i].y - p[i].x * p[i].x;
        if (p[i].x < p[id].x || (p[i].x == p[id].x && p[i].y < p[id].y))
            id = i;
    }
    swap(p[1], p[id]);
    sort(p + 2, p + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        while (top > 1 && ((p[i] - p[st[top - 1]]) ^ (p[i] - p[st[top]])) >= 0)
            --top;
        st[++top] = i;
    }
    for (int i = 2; i <= top; ++i)
        if (p[st[i]].x < p[st[i - 1]].x)
        {
            top = i - 1;
            break;
        }
    while (top > 1 && p[st[top]].x == p[st[top - 1]].x)
        --top;
    if (top > 1 && p[st[1]].x == p[st[2]].x)
        --top;
    printf("%d", top - 1);
    return 0;
}