#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n, sum = 1, top, col, co;
int v[100005], w[100005];
int head[100005];
int st[100005], val[100005];
int use[100005], flg[100005];
int vis[200005];
ll ans;
vector<int> vec[100005];
struct edge
{
    int v;
    int w;
    int nxt;
} a[200005];
struct node
{
    int a;
    int b;
} f[100005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k)
{
    use[k] = 1;
    st[++top] = k;
    flg[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[d | 1])
        {
            val[k] = a[d].w;
            vis[d | 1] = 1;
            if (!flg[a[d].v])
                dfs(a[d].v);
            else
            {
                ++col;
                int tmp = top;
                while (st[tmp] != a[d].v)
                {
                    vec[col].push_back(val[st[tmp]]);
                    --tmp;
                }
                vec[col].push_back(val[st[tmp]]);
                sort(vec[col].begin(), vec[col].end());
            }
        }
        d = a[d].nxt;
    }
    --top;
    flg[k] = 0;
    return false;
}
bool cmp(node aa, node bb)
{
    return aa.a - aa.b > bb.a - bb.b;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &v[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i <= n; ++i)
    {
        ins(i, v[i], w[i]);
        ins(v[i], i, w[i]);
        ans += w[i];
    }
    for (int i = 1; i <= n; ++i)
        if (!use[i])
            dfs(i);
    for (int i = 1; i <= col; ++i)
    {
        int siz = vec[i].size();
        if (siz & 1)
            ans -= vec[i][siz / 2];
        else
        {
            ++co;
            f[co].a = vec[i][siz / 2];
            f[co].b = vec[i][siz / 2 - 1];
        }
    }
    sort(f + 1, f + co + 1, cmp);
    for (int i = 1; i <= co; ++i)
        if (i & 1)
            ans -= f[i].a;
        else
            ans -= f[i].b;
    printf("%lld", ans);
    return 0;
}