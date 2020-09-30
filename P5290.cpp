#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int n, sum, head[200005], m[200005];
long long ans;
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
priority_queue<int> dfs(int k)
{
    priority_queue<int> p, q;
    int d = head[k];
    while (d)
    {
        p = dfs(a[d].v);
        if (p.size() > q.size())
            swap(p, q);
        int siz = p.size();
        priority_queue<int> o;
        for (int i = 0; i < siz; ++i)
        {
            o.push(max(p.top(), q.top()));
            p.pop();
            q.pop();
        }
        for (int i = 0; i < siz; ++i)
        {
            q.push(o.top());
            o.pop();
        }
        d = a[d].nxt;
    }
    q.push(m[k]);
    return q;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &m[i]);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        scanf("%d", &fa);
        ins(fa, i);
    }
    priority_queue<int> q = dfs(1);
    int siz = q.size();
    for (int i = 0; i < siz; ++i)
    {
        ans += q.top();
        q.pop();
    }
    printf("%lld", ans);
    return 0;
}