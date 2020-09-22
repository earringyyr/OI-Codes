#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define mp make_pair
#define pii pair<int, int>
using namespace std;
int n, m, cnt, num, sum;
int a[100005], b[100005];
int pre[100005], nxt[100005];
int vis[100005];
priority_queue<pii, vector<pii>, greater<pii> > q;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    for (int i = 2; i <= n; ++i)
        if ((b[i - 1] > 0) == (b[i] > 0))
            b[i] += b[i - 1];
        else
        {
            if (b[i - 1] > 0)
            {
                sum += b[i - 1];
                ++num;
            }
            a[++cnt] = b[i - 1];
        }
    if (b[n] > 0)
    {
        sum += b[n];
        ++num;
    }
    a[++cnt] = b[n];
    for (int i = 1; i <= cnt; ++i)
    {
        pre[i] = i - 1;
        nxt[i] = i + 1;
        q.push(mp(abs(a[i]), i));
    }
    while (num > m)
    {
        int k = q.top().first, x = q.top().second;
        q.pop();
        if (abs(a[x]) != k || vis[x])
            continue;
        --num;
        sum -= k;
        if (pre[x] == 0)
        {
            if (a[x] < 0)
            {
                ++num;
                sum += k;
            }
            else
            {
                a[nxt[x]] = a[nxt[x]] + a[x];
                q.push(mp(abs(a[nxt[x]]), nxt[x]));
            }
            vis[x] = 1;
            pre[nxt[x]] = 0;
        }
        else if (nxt[x] == cnt + 1)
        {
            if (a[x] < 0)
            {
                ++num;
                sum += k;
            }
            else
            {
                a[pre[x]] = a[pre[x]] + a[x];
                q.push(mp(abs(a[pre[x]]), pre[x]));
            }
            vis[x] = 1;
            nxt[pre[x]] = cnt + 1;
        }
        else
        {
            if (nxt[nxt[x]] != cnt + 1)
                pre[nxt[nxt[x]]] = x;
            if (pre[pre[x]] != 0)
                nxt[pre[pre[x]]] = x;
            vis[pre[x]] = 1;
            vis[nxt[x]] = 1;
            a[x] = a[x] + a[pre[x]] + a[nxt[x]];
            pre[x] = pre[pre[x]];
            nxt[x] = nxt[nxt[x]];
            q.push(mp(abs(a[x]), x));
        }
    }
    printf("%d\n", sum);
    return 0;
}