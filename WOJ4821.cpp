#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;
int n, sum, w[200005], num[200005], head[200005], dep[200005];
long long ans;
struct node
{
    int v;
    int nxt;
} a[400005];
struct point
{
    int id;
    int val;
    point(int aa, int bb)
    {
        id = aa;
        val = bb;
    }
};
vector<point> v[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int gcd(int a, int b)
{
    if (!b)
        return a;
    return gcd(b, a % b);
}
void dfs(int k, int fa)
{
    v[k] = v[fa];
    v[k].push_back(point(k, w[k]));
    for (int i = 0; i < v[k].size(); ++i)
    {
        v[k][i] = point(v[k][i].id, gcd(v[k][i].val, w[k]));
        ans = max(ans, (long long)(dep[k] - dep[v[k][i].id] + 1) * v[k][i].val);
    }
    int j = 0;
    for (int i = 0; i < v[k].size(); ++i)
        if (v[k][i].val != v[k][i - 1].val)
            v[k][j++] = v[k][i];
    while (v[k].size() > j)
        v[k].pop_back();
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
}
int main()
{
    int size = 40 << 20; //40M
    //__asm__ ("movl  %0, %%esp\n"::"r"((char*)malloc(size)+size));//调试用这个
    __asm__("movq %0,%%rsp\n" ::"r"((char *)malloc(size) + size)); //提交用这个
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
        ++num[u];
        ++num[v];
    }
    for (int i = 1; i <= n; ++i)
        if (num[i] == 1)
        {
            dep[i] = 0;
            dfs(i, 0);
        }
    printf("%lld", ans);
    exit(0);
}