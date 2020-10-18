#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m;
int pp[300005], pv[300005];
int lp[3000005], rp[3000005];
int lv[3000005], rv[3000005];
ll maxn, minx;
struct node
{
    int id;
    int num;
} p[300005], v[300005];
bool cmp(node aa, node bb)
{
    return aa.num < bb.num;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        p[i].id = i;
        scanf("%d", &p[i].num);
    }
    for (int i = 1; i <= n; ++i)
    {
        v[i].id = i;
        scanf("%d", &v[i].num);
    }
    sort(p + 1, p + n + 1, cmp);
    sort(v + 1, v + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        if (i == 1 || p[i].num != p[i - 1].num)
            lp[p[i].num + 1500000] = i;
        rp[p[i].num + 1500000] = i;
        if (i == 1 || v[i].num != v[i - 1].num)
            lv[v[i].num + 1500000] = i;
        rv[v[i].num + 1500000] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        pp[p[i].id] = i;
        pv[v[i].id] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        maxn += (ll)p[i].num * v[i].num;
        minx += (ll)p[n - i + 1].num * v[i].num;
    }
    printf("%lld %lld\n", minx, maxn);
    for (int i = 1; i <= m; ++i)
    {
        int ty, x, delta;
        scanf("%d%d%d", &ty, &x, &delta);
        if (ty == 1)
        {
            x = pp[x];
            if (delta == 1)
            {
                swap(pp[p[x].id], pp[p[rp[p[x].num + 1500000]].id]);
                swap(p[x], p[rp[p[x].num + 1500000]]);
                x = rp[p[x].num + 1500000];
                --rp[p[x].num + 1500000];
                if (lp[p[x].num + 1500000] > rp[p[x].num + 1500000])
                {
                    lp[p[x].num + 1500000] = 0;
                    rp[p[x].num + 1500000] = 0;
                }
                ++p[x].num;
                if (x == n || p[x + 1].num != p[x].num)
                {
                    lp[p[x].num + 1500000] = x;
                    rp[p[x].num + 1500000] = x;
                }
                else
                    --lp[p[x].num + 1500000];
                maxn += v[x].num;
                minx += v[n - x + 1].num;
            }
            else
            {
                swap(pp[p[x].id], pp[p[lp[p[x].num + 1500000]].id]);
                swap(p[x], p[lp[p[x].num + 1500000]]);
                x = lp[p[x].num + 1500000];
                ++lp[p[x].num + 1500000];
                if (lp[p[x].num + 1500000] > rp[p[x].num + 1500000])
                {
                    lp[p[x].num + 1500000] = 0;
                    rp[p[x].num + 1500000] = 0;
                }
                --p[x].num;
                if (x == 1 || p[x - 1].num != p[x].num)
                {
                    lp[p[x].num + 1500000] = x;
                    rp[p[x].num + 1500000] = x;
                }
                else
                    ++rp[p[x].num + 1500000];
                maxn -= v[x].num;
                minx -= v[n - x + 1].num;
            }
        }
        else
        {
            x = pv[x];
            if (delta == 1)
            {
                swap(pv[v[x].id], pv[v[rv[v[x].num + 1500000]].id]);
                swap(v[x], v[rv[v[x].num + 1500000]]);
                x = rv[v[x].num + 1500000];
                --rv[v[x].num + 1500000];
                if (lv[v[x].num + 1500000] > rv[v[x].num + 1500000])
                {
                    lv[v[x].num + 1500000] = 0;
                    rv[v[x].num + 1500000] = 0;
                }
                ++v[x].num;
                if (x == n || v[x + 1].num != v[x].num)
                {
                    lv[v[x].num + 1500000] = x;
                    rv[v[x].num + 1500000] = x;
                }
                else
                    --lv[v[x].num + 1500000];
                maxn += p[x].num;
                minx += p[n - x + 1].num;
            }
            else
            {
                swap(pv[v[x].id], pv[v[lv[v[x].num + 1500000]].id]);
                swap(v[x], v[lv[v[x].num + 1500000]]);
                x = lv[v[x].num + 1500000];
                ++lv[v[x].num + 1500000];
                if (lv[v[x].num + 1500000] > rv[v[x].num + 1500000])
                {
                    lv[v[x].num + 1500000] = 0;
                    rv[v[x].num + 1500000] = 0;
                }
                --v[x].num;
                if (x == 1 || v[x - 1].num != v[x].num)
                {
                    lv[v[x].num + 1500000] = x;
                    rv[v[x].num + 1500000] = x;
                }
                else
                    ++rv[v[x].num + 1500000];
                maxn -= p[x].num;
                minx -= p[n - x + 1].num;
            }
        }
        printf("%lld %lld\n", minx, maxn);
    }
    return 0;
}