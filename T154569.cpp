#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 0x7f7f7f7f7f7f7f7f;
int n, P, num;
int fa[100005], a[100005];
int pfa[100005][2], nfa[100005][2];
ll ans;
ll minx[100005], id[100005];
ll val[100005][2], pre[100005][2], nxt[100005][2];
int getfather(int x)
{
    if (fa[x] == x)
        return fa[x];
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d", &n, &P);
    num = n;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        fa[i] = i;
        val[i][0] = a[i] - (ll)i * P;
        val[i][1] = a[i] + (ll)i * P;
    }
    while (num > 1)
    {
        pre[0][0] = inf;
        pre[0][1] = inf;
        for (int i = 1; i <= n; ++i)
        {
            pre[i][0] = pre[i - 1][0];
            pre[i][1] = pre[i - 1][1];
            pfa[i][0] = pfa[i - 1][0];
            pfa[i][1] = pfa[i - 1][1];
            if (val[i][0] < pre[i][0])
            {
                if (pfa[i][0] == getfather(i))
                    pre[i][0] = val[i][0];
                else
                {
                    pre[i][1] = pre[i][0];
                    pfa[i][1] = pfa[i][0];
                    pre[i][0] = val[i][0];
                    pfa[i][0] = getfather(i);
                }
            }
            else if (val[i][0] < pre[i][1] && pfa[i][0] != getfather(i))
            {
                pre[i][1] = val[i][0];
                pfa[i][1] = getfather(i);
            }
        }
        nxt[n + 1][0] = inf;
        nxt[n + 1][1] = inf;
        for (int i = n; i >= 1; --i)
        {
            nxt[i][0] = nxt[i + 1][0];
            nxt[i][1] = nxt[i + 1][1];
            nfa[i][0] = nfa[i + 1][0];
            nfa[i][1] = nfa[i + 1][1];
            if (val[i][1] < nxt[i][0])
            {
                if (nfa[i][0] == getfather(i))
                    nxt[i][0] = val[i][1];
                else
                {
                    nxt[i][1] = nxt[i][0];
                    nfa[i][1] = nfa[i][0];
                    nxt[i][0] = val[i][1];
                    nfa[i][0] = getfather(i);
                }
            }
            else if (val[i][1] < nxt[i][1] && nfa[i][0] != getfather(i))
            {
                nxt[i][1] = val[i][1];
                nfa[i][1] = getfather(i);
            }
        }
        memset(minx, 0x7f, sizeof(minx));
        for (int i = 1; i <= n; ++i)
        {
            if (pfa[i][0] != getfather(i))
            {
                if (pre[i][0] + val[i][1] < minx[getfather(i)])
                {
                    minx[getfather(i)] = pre[i][0] + val[i][1];
                    id[getfather(i)] = pfa[i][0];
                }
            }
            else
            {
                if (pre[i][1] + val[i][1] < minx[getfather(i)])
                {
                    minx[getfather(i)] = pre[i][1] + val[i][1];
                    id[getfather(i)] = pfa[i][1];
                }
            }
            if (nfa[i][0] != getfather(i))
            {
                if (nxt[i][0] + val[i][0] < minx[getfather(i)])
                {
                    minx[getfather(i)] = nxt[i][0] + val[i][0];
                    id[getfather(i)] = nfa[i][0];
                }
            }
            else
            {
                if (nxt[i][1] + val[i][0] < minx[getfather(i)])
                {
                    minx[getfather(i)] = nxt[i][1] + val[i][0];
                    id[getfather(i)] = nfa[i][1];
                }
            }
        }
        for (int i = 1; i <= n; ++i)
            if (getfather(i) == i)
            {
                int u = i, v = getfather(id[i]);
                if (u != v)
                {
                    fa[u] = v;
                    ans += minx[i];
                    --num;
                }
            }
    }
    printf("%lld", ans);
    return 0;
}