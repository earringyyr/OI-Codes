#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
vector<int> son[100005];
unordered_map<unsigned long long, int> vis;
int n, sum, cnt, top;
int head[100005], st[100005], en[100005], dep[100005], dfn[200005], s[200005];
unsigned long long base = 17171, h[200005], hsh[200005];
struct node
{
    int v;
    int nxt;
} a[100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
unsigned long long gethash(int l, int r)
{
    return hsh[r] - hsh[l - 1] * h[r - l + 1];
}
void dfs1(int k)
{
    ++cnt;
    st[k] = cnt;
    dfn[cnt] = 233;
    int d = head[k];
    while (d)
    {
        dfs1(a[d].v);
        dep[k] = max(dep[k], dep[a[d].v]);
        d = a[d].nxt;
    }
    ++cnt;
    en[k] = cnt;
    dfn[cnt] = 959;
    ++dep[k];
    return;
}
void dfs2(int k, int num)
{
    s[++top] = k;
    if (top > num)
        son[s[top - num]].push_back(k);
    int d = head[k];
    while (d)
    {
        dfs2(a[d].v, num);
        d = a[d].nxt;
    }
    --top;
    return;
}
bool check(int k)
{
    vis.clear();
    for (int i = 1; i <= n; ++i)
        son[i].clear();
    dfs2(1, k);
    for (int i = 1; i <= n; ++i)
        if (dep[i] > k)
        {
            int l = st[i], siz = son[i].size();
            unsigned long long num = 0;
            for (int j = 0; j < siz; ++j)
            {
                int r = st[son[i][j]];
                num = num * h[r - l + 1] + gethash(l, r);
                l = en[son[i][j]];
            }
            int r = en[i];
            num = num * h[r - l + 1] + gethash(l, r);
            if (vis[num])
                return true;
            vis[num] = 1;
        }
    return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        for (int j = 1; j <= x; ++j)
        {
            int v;
            scanf("%d", &v);
            ins(i, v);
        }
    }
    dfs1(1);
    h[0] = 1;
    for (int i = 1; i <= cnt; ++i)
        h[i] = h[i - 1] * base;
    for (int i = 1; i <= cnt; ++i)
        hsh[i] = hsh[i - 1] * base + dfn[i];
    check(3);
    int lef = 0, rig = dep[1] - 1;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (check(mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    printf("%d", lef);
    return 0;
}