#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define int unsigned long long
using namespace std;
const int mod = 2147483648;
int sum, pos = 1;
int vis[100005], pri[100005], mu[100005], num[100005], cnt[100005], c[100005], ans[20005];
struct node
{
    int a;
    int b;
    node(int aa = 0, int bb = 0)
    {
        a = aa;
        b = bb;
    }
} f[100005];
struct ask
{
    int id;
    int n;
    int m;
    int a;
} q[20005];
bool comp(node aa, node bb)
{
    return aa.b < bb.b;
}
bool cmp(ask aa, ask bb)
{
    return aa.a < bb.a;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= 100000)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
int solve(int n, int m)
{
    int num = 0;
    if (m < n)
        swap(m, n);
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(m / (m / l), n / (n / l));
        num += (n / l) * (m / l) * (ask(r) - ask(l - 1));
    }
    return num;
}
signed main()
{
    mu[1] = 1;
    num[1] = 1;
    f[1] = node(1, 1);
    for (int i = 2; i <= 100000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
            mu[i] = -1;
            num[i] = i + 1;
            cnt[i] = 1;
            f[i] = node(i, num[i]);
        }
        for (int j = 1; j <= sum && pri[j] <= vis[i] && i * pri[j] <= 100000; ++j)
        {
            if (pri[j] == vis[i])
            {
                mu[i * pri[j]] = 0;
                num[i * pri[j]] = num[i] * pri[j] + cnt[i];
                cnt[i * pri[j]] = cnt[i];
            }
            else
            {
                mu[i * pri[j]] = mu[i] * mu[pri[j]];
                num[i * pri[j]] = num[i] * pri[j] + num[i];
                cnt[i * pri[j]] = num[i];
            }
            vis[i * pri[j]] = pri[j];
            f[i * pri[j]] = node(i * pri[j], num[i * pri[j]]);
        }
    }
    sort(f + 1, f + 100001, comp);
    int Q;
    scanf("%llu", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        q[i].id = i;
        scanf("%llu%llu%llu", &q[i].n, &q[i].m, &q[i].a);
    }
    sort(q + 1, q + Q + 1, cmp);
    for (int i = 1; i <= Q; ++i)
    {
        while (q[i].a >= f[pos].b && pos <= 100000)
        {
            for (int j = f[pos].a; j <= 100000; j += f[pos].a)
                add(j, f[pos].b * mu[j / f[pos].a]);
            ++pos;
        }
        ans[q[i].id] = solve(q[i].n, q[i].m);
    }
    for (int i = 1; i <= Q; ++i)
        printf("%llu\n", ans[i] % mod);
    return 0;
}