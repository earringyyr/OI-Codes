#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 0x7fffffffffffffff;
int n, m, G, S, cnt;
int fa[205];
ll ans = inf;
struct node
{
    int u;
    int v;
    int g;
    int s;
} a[50005], b[205];
bool cmp1(node aa, node bb)
{
    return aa.g < bb.g;
}
bool cmp2(node aa, node bb)
{
    return aa.s < bb.s;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d", &G, &S);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].g, &a[i].s);
    sort(a + 1, a + m + 1, cmp1);
    for (int i = 1; i <= m; ++i)
    {
        b[++cnt] = a[i];
        for (int j = 1; j <= n; ++j)
            fa[j] = j;
        sort(b + 1, b + cnt + 1, cmp2);
        int tmp = cnt;
        cnt = 0;
        for (int j = 1; j <= tmp; ++j)
            if (getfather(b[j].u) != getfather(b[j].v))
            {
                b[++cnt] = b[j];
                fa[getfather(b[j].u)] = getfather(b[j].v);
                if (cnt == n - 1)
                {
                    ans = min(ans, (ll)a[i].g * G + (ll)b[j].s * S);
                    break;
                }
            }
    }
    if (ans == inf)
        printf("-1");
    else
        printf("%lld", ans);
    return 0;
}