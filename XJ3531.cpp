#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, cnt, ans = 1, now, nxt = 1;
int fa[25], siz[25];
int f[2][5005];
vector<int> tmp;
vector<int> p, q;
vector<int> vec[5005];
map<vector<int>, int> mp;
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void init(int res, int lst)
{
    if (tmp.size() > 10)
        return;
    if (!res)
    {
        ++cnt;
        mp[tmp] = cnt;
        vec[cnt] = tmp;
        return;
    }
    for (int i = lst; i <= res; ++i)
    {
        tmp.push_back(i);
        init(res - i, i);
        tmp.pop_back();
    }
    return;
}
void dfs(int k, int w, int num, int siz, int col)
{
    if (vec[0].size() - k < num)
        return;
    if (k == vec[0].size())
    {
        vector<int> temp = tmp;
        if (siz)
            temp.push_back(siz);
        sort(temp.begin(), temp.end());
        f[nxt][mp[temp]] = (f[nxt][mp[temp]] + col) % mod;
        return;
    }
    tmp.push_back(vec[0][k]);
    dfs(k + 1, w, num, siz, col);
    tmp.pop_back();
    if (num > 0)
        dfs(k + 1, w + 1, num - 1, siz + vec[0][k] - 1, (ll)col * num % mod * vec[0][k] % mod);
    return;
}
int main()
{
    for (int i = 0; i <= 20; ++i)
        init(i, 1);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        siz[i] = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u = getfather(u);
        v = getfather(v);
        if (u != v)
            fa[u] = v;
    }
    for (int i = 1; i <= n; ++i)
        ++siz[getfather(i)];
    for (int i = 1; i <= n; ++i)
        if (getfather(i) == i)
            p.push_back(siz[i]);
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        siz[i] = 0;
    }
    for (int i = 1; i <= n - m - 1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u = getfather(u);
        v = getfather(v);
        if (u != v)
            fa[u] = v;
    }
    for (int i = 1; i <= n; ++i)
        ++siz[getfather(i)];
    for (int i = 1; i <= n; ++i)
        if (getfather(i) == i)
            q.push_back(siz[i]);
    sort(p.begin(), p.end());
    sort(q.begin(), q.end());
    if (p.size() < q.size())
        swap(p, q);
    f[now][mp[q]] = 1;
    for (int i = p.size() - 1; i >= 0; --i)
    {
        memset(f[nxt], 0, sizeof(f[nxt]));
        for (int j = 1; j <= cnt; ++j)
            if (f[now][j])
            {
                vec[0] = vec[j];
                dfs(0, 0, p[i], 0, f[now][j]);
            }
        swap(now, nxt);
    }
    printf("%d", f[now][1]);
    return 0;
}