#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
int n, k, sum, ans;
int a[1000005], A[1000005];
int head[1000005];
char buf[1 << 21], *p1, *p2;
set<pii> s;
struct node
{
    int v;
    int w;
    int nxt;
} e[1000005];
int read()
{
    int x = 0;
    char ch = gc();
    while (!isdigit(ch))
        ch = gc();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x;
}
void ins(int u, int v, int w)
{
    ++sum;
    e[sum].v = v;
    e[sum].w = w;
    e[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int type)
{
    if (!type)
    {
        int maxn = 0;
        int d = head[k];
        while (d)
        {
            maxn = max(maxn, e[d].w);
            d = e[d].nxt;
        }
        ans = min(ans, maxn - 1);
        d = head[k];
        while (d)
        {
            if (head[e[d].v])
            {
                if (e[d].w != maxn)
                    dfs(e[d].v, 0);
                else
                    dfs(e[d].v, 1);
            }
            d = e[d].nxt;
        }
    }
    else
    {
        int d = head[k];
        while (d)
        {
            if (head[e[d].v])
                dfs(e[d].v, 0);
            d = e[d].nxt;
        }
    }
    return;
}
int main()
{
    int T;
    T = read();
    for (int tt = 1; tt <= T; ++tt)
    {
        s.clear();
        sum = 0;
        memset(head, 0, sizeof(head));
        if (tt == 1)
        {
            n = read();
            for (int i = 1; i <= n; ++i)
                A[i] = read();
        }
        else
        {
            k = read();
            for (int i = 1; i <= k; ++i)
            {
                int x, y;
                x = read();
                y = read();
                A[x] = y;
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            a[i] = A[i];
            s.insert(mp(A[i], i));
        }
        for (int i = 1; i < n; ++i)
        {
            set<pii>::iterator x = s.begin(), y = --s.end();
            int xx = (*x).second, yy = (*y).second;
            ins(yy, xx, i);
            a[yy] -= a[xx];
            pii tmp = mp(a[yy], yy);
            s.erase(x);
            s.erase(y);
            s.insert(tmp);
        }
        ans = n - 1;
        int x = (*s.begin()).second;
        dfs(x, 1);
        printf("%d\n", n - ans);
    }
    return 0;
}