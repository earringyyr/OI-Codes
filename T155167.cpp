#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
int n, a[300005];
ll ans = -1e18, pre[300005], nxt[300005];
priority_queue<int, vector<int>, greater<int> > p;
priority_queue<int> q;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 3 * n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        p.push(a[i]);
        pre[n] += a[i];
    }
    for (int i = 2 * n + 1; i <= 3 * n; ++i)
    {
        q.push(a[i]);
        nxt[2 * n + 1] += a[i];
    }
    for (int i = n + 1; i <= 2 * n; ++i)
    {
        pre[i] = pre[i - 1];
        if (a[i] > p.top())
        {
            pre[i] -= p.top();
            p.pop();
            pre[i] += a[i];
            p.push(a[i]);
        }
    }
    for (int i = 2 * n; i >= n + 1; --i)
    {
        nxt[i] = nxt[i + 1];
        if (a[i] < q.top())
        {
            nxt[i] -= q.top();
            q.pop();
            nxt[i] += a[i];
            q.push(a[i]);
        }
    }
    for (int i = n; i <= 2 * n; ++i)
        ans = max(ans, pre[i] - nxt[i + 1]);
    printf("%lld", ans);
    return 0;
}