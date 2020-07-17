#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n, p, q;
ll ans;
struct node
{
    int x;
    int y;
} c[100005];
bool cmp(node aa, node bb)
{
    return (ll)aa.x * bb.y > (ll)aa.y * bb.x;
}
int main()
{
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &c[i].x, &c[i].y);
    sort(c + 1, c + n + 1, cmp);
    ans = min((ll)ceil((double)c[n].y / c[n].x) * p, (ll)ceil((double)c[1].x / c[1].y) * p + q);
    for (int i = 1; i < n; ++i)
    {
        node u = c[i], v = c[i + 1];
        if (u.x * v.y == u.y * v.x)
            continue;
        ll num = 0;
        while (true)
        {
            if (u.x >= u.y && v.x >= v.y)
            {
                swap(u.x, u.y);
                swap(v.x, v.y);
                num += q;
            }
            else if (u.x < u.y && v.x < v.y)
            {
                int cnt = min((u.y - 1) / u.x, (v.y - 1) / v.x);
                u.y -= cnt * u.x;
                v.y -= cnt * v.x;
                num += (ll)cnt * p;
            }
            else
            {
                if (u.x >= u.y)
                    swap(u, v);
                ll tmp = 0;
                node w = u;
                w.y -= w.x;
                tmp = p + q + (ll)ceil((double)w.x / w.y) * p;
                if (v.x != v.y)
                {
                    w = v;
                    swap(w.x, w.y);
                    w.y -= w.x;
                    tmp = min(tmp, p + 2 * q + (ll)ceil((double)w.x / w.y) * p);
                }
                num += tmp;
                break;
            }
        }
        ans = min(ans, num);
    }
    printf("%lld", ans);
    return 0;
}