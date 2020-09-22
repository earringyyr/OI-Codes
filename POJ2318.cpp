#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, x1, y1, x2, y2, num[5005];
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
    ll operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    ll operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} q, p[5005], pp[5005];
int main()
{
    while (scanf("%d", &n) == 1)
    {
        if (!n)
            break;
        scanf("%d%lld%lld%lld%lld", &m, &p[0].x, &p[0].y, &pp[0].x, &pp[0].y);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld%lld", &p[i].x, &pp[i].x);
            p[i].y = p[0].y;
            pp[i].y = pp[0].y;
        }
        for (int i = 1; i <= m; ++i)
        {
            scanf("%lld%lld", &q.x, &q.y);
            int l = 0, r = n;
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (((q - pp[mid]) ^ (p[mid] - pp[mid])) > 0)
                    l = mid;
                else
                    r = mid - 1;
            }
            ++num[l];
        }
        for (int i = 0; i <= n; ++i)
        {
            printf("%d: %d\n", i, num[i]);
            num[i] = 0;
        }
        putchar('\n');
    }
    return 0;
}