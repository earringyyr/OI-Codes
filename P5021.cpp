#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
int n, m, sum, num, mid, head[50005];
int f[50005], dp[50005], go[50005], use[50005];
multiset<int> s;
struct node
{
    int v;
    int w;
    int next;
} a[100005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int w, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, a[d].w, k);
            dp[k] += dp[a[d].v];
        }
        d = a[d].next;
    }
    s.clear();
    int cnt = 0, sum = 0;
    d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            ++cnt;
            s.insert(f[a[d].v]);
        }
        d = a[d].next;
    }
    while (!s.empty())
    {
        multiset<int>::iterator zuo, you;
        zuo = s.begin();
        go[++sum] = *zuo;
        s.erase(zuo);
        you = s.lower_bound(mid - go[sum]);
        if (you != s.end())
        {
            dp[k]++;
            sum--;
            s.erase(you);
        }
    }
    while (!s.empty())
    {
        go[++sum] = *s.begin();
        s.erase(s.begin());
    }
    int ma = go[sum];
    if (ma + w >= mid)
        dp[k]++;
    else
        f[k] = ma + w;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int aa, bb, l;
        scanf("%d%d%d", &aa, &bb, &l);
        num += l;
        ins(aa, bb, l);
        ins(bb, aa, l);
    }
    int zuo = 0, you = num;
    while (zuo < you)
    {
        memset(f, 0, sizeof(f));
        memset(dp, 0, sizeof(dp));
        mid = (zuo + you + 1) / 2;
        dfs(1, 0, 0);
        if (dp[1] >= m)
            zuo = mid;
        else
            you = mid - 1;
    }
    cout << zuo;
    return 0;
}