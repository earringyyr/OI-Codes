#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int n, sum;
int head[100005], a[100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u = i, v;
        scanf("%d", &v);
        ins(u, v);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    dfs(1);
    return 0;
}