#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
int sum, x, y, cnt;
int id[400005], pos[400005], dis[400005];
vector<int> B[200005], G[200005];
ll ans, num;
int exgcd(int a, int b)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    int tmp = exgcd(b, a % b);
    int xx = x;
    x = y;
    y = xx - a / b * y;
    return tmp;
}
bool cmp(int aa, int bb)
{
    if (dis[aa] != dis[bb])
        return dis[aa] < dis[bb];
    return aa > bb;
}
ll solve(int n, int m, int w, vector<int> b, vector<int> g)
{
    if (n == b.size())
        return -1;
    cnt = 0;
    for (int i = 0; i < b.size(); ++i)
    {
        ++cnt;
        id[cnt] = cnt;
        pos[cnt] = b[i];
        dis[cnt] = (ll)b[i] * w % n;
    }
    for (int i = 0; i < g.size(); ++i)
    {
        ++cnt;
        id[cnt] = cnt;
        pos[cnt] = g[i];
        dis[cnt] = (ll)g[i] * w % n;
    }
    sort(id + 1, id + cnt + 1, cmp);
    id[0] = 0;
    dis[0] = dis[id[cnt]] - n;
    id[cnt + 1] = cnt + 1;
    dis[cnt + 1] = dis[id[1]] + n;
    ll minx = 1e18;
    for (int i = 1; i <= cnt; ++i)
        minx = min((ll)pos[id[i]], minx + (ll)(dis[id[i]] - dis[id[i - 1]]) * m);
    num = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        minx = min((ll)pos[id[i]], minx + (ll)(dis[id[i]] - dis[id[i - 1]]) * m);
        if (dis[id[i]] == dis[id[i + 1]])
            continue;
        num = max(num, minx);
        if (dis[id[i]] + 1 == dis[id[i + 1]])
            continue;
        num = max(num, minx + (ll)(dis[id[i + 1]] - dis[id[i]] - 1) * m);
    }
    return num;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int d = exgcd(n, m);
    x = (x + m / d) % (m / d);
    y = (y + n / d) % (n / d);
    int tmp, lenb, leng;
    scanf("%d", &lenb);
    for (int i = 1; i <= lenb; ++i)
    {
        scanf("%d", &tmp);
        B[tmp % d].push_back(tmp / d);
    }
    scanf("%d", &leng);
    for (int i = 1; i <= leng; ++i)
    {
        scanf("%d", &tmp);
        G[tmp % d].push_back(tmp / d);
    }
    if (d > lenb + leng)
    {
        printf("-1");
        return 0;
    }
    for (int i = 0; i < d; ++i)
    {
        if (!B[i].size() && !G[i].size())
        {
            printf("-1");
            return 0;
        }
        ans = max(ans, (ll)solve(n / d, m / d, y, B[i], G[i]) * d + i);
        ans = max(ans, (ll)solve(m / d, n / d, x, G[i], B[i]) * d + i);
    }
    printf("%lld", ans);
    return 0;
}