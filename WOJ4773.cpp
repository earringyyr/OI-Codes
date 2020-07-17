#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define inf 0x3f3f3f3f3f3f3f3fLL
using namespace std;
int n, m, qq, out[100005], v[100005][32];
long long siz[100005], s[100005][32];
queue<int> q;
vector<long long> sum[100005];
vector<int> son[100005], fa[100005];
int query(int k, int d)
{
    if (!d)
        return k;
    for (int i = 31; i >= 0; --i)
        if (v[k][i] && s[k][i] <= d && siz[v[k][i]] + s[k][i] >= d)
            return query(v[k][i], d - s[k][i]);
    int p = (--lower_bound(sum[k].begin(), sum[k].end(), d)) - sum[k].begin();
    if (p != -1)
        d -= sum[k][p];
    return query(son[k][p + 1], d - 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ++out[x];
        son[x].push_back(y);
        fa[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        if (!out[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int d = 0; d < son[u].size(); ++d)
        {
            siz[u] += (siz[son[u][d]] + 1);
            siz[u] = min(siz[u], inf);
            sum[u].push_back(siz[u]);
        }
        if (son[u].size())
        {
            int p = 0;
            for (int d = 1; d < son[u].size(); ++d)
                if (siz[son[u][d]] > siz[son[u][p]])
                    p = d;
            s[u][0] = 1;
            v[u][0] = son[u][p];
            for (int d = 0; d < p; d++)
            {
                s[u][0] += siz[son[u][d]] + 1;
                s[u][0] = min(s[u][0], inf);
            }
            for (int i = 1; i < 31; i++)
            {
                v[u][i] = v[v[u][i - 1]][i - 1];
                if (!v[u][i])
                    break;
                s[u][i] = s[u][i - 1] + s[v[u][i - 1]][i - 1];
                s[u][i] = min(s[u][i], inf);
            }
        }
        for (int d = 0; d < fa[u].size(); ++d)
        {
            int v = fa[u][d];
            --out[v];
            if (!out[v])
                q.push(v);
        }
    }
    scanf("%d", &qq);
    for (int i = 1; i <= qq; i++)
    {
        int ss, k;
        scanf("%d%d", &ss, &k);
        if (siz[ss] < k)
            puts("-1");
        else
            printf("%d\n", query(ss, k));
    }
}