#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
int n, sum, rt, mul;
int head[1005], siz[1005], f[1005];
struct edge
{
    int v;
    int nxt;
} a[2005];
struct node
{
    int siz;
    vector<int> vec;
    node(int aa = 0, vector<int> bb = vector<int>())
    {
        siz = aa;
        vec = bb;
    }
    bool operator<(const node &bb) const
    {
        return siz > bb.siz;
    }
};
priority_queue<node> q;
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = max(f[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    f[k] = max(f[k], n - siz[k]);
    if (f[k] < f[rt])
        rt = k;
    return;
}
void dfs2(int k, int fa)
{
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs2(a[d].v, k);
            siz[k] += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
void dfs(int k, int fa)
{
    int cnt = 0, d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            printf("%d %d %d\n", k, a[d].v, (cnt + 1) * mul);
            dfs(a[d].v, k);
            cnt += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    if (n == 1)
        return 0;
    if (n == 2)
    {
        printf("1 2 1");
        return 0;
    }
    f[0] = n;
    dfs1(1, 0);
    dfs2(rt, 0);
    int d = head[rt];
    while (d)
    {
        vector<int> tmp;
        tmp.push_back(a[d].v);
        q.push(node(siz[a[d].v], tmp));
        d = a[d].nxt;
    }
    while (q.size() >= 3)
    {
        node aa = q.top();
        q.pop();
        node bb = q.top();
        q.pop();
        aa.siz += bb.siz;
        for (int i = 0; i < bb.vec.size(); ++i)
            aa.vec.push_back(bb.vec[i]);
        q.push(aa);
    }
    node aa = q.top();
    q.pop();
    node bb = q.top();
    q.pop();
    mul = 1;
    int cnt = 0;
    for (int i = 0; i < aa.vec.size(); ++i)
    {
        printf("%d %d %d\n", rt, aa.vec[i], (cnt + 1) * mul);
        dfs(aa.vec[i], rt);
        cnt += siz[aa.vec[i]];
    }
    mul = cnt + 1;
    cnt = 0;
    for (int i = 0; i < bb.vec.size(); ++i)
    {
        printf("%d %d %d\n", rt, bb.vec[i], (cnt + 1) * mul);
        dfs(bb.vec[i], rt);
        cnt += siz[bb.vec[i]];
    }
    return 0;
}