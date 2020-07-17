#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n, m, p, sum = 1, head[200005], x[200005], vis[200005], fa[200005];
long long ans[200005], d[200005];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c & 15);
        c = gc();
    }
    return x * f;
}
char bbuf[1 << 21];
int pp1 = -1;
const int pp2 = (1 << 21) - 1;
inline void flush()
{
    fwrite(bbuf, 1, pp1 + 1, stdout);
    pp1 = -1;
    return;
}
inline void pc(char x)
{
    if (pp1 == pp2)
        flush();
    bbuf[++pp1] = x;
    return;
}
inline void write(long long x)
{
    char buffer[10];
    int len = -1;
    if (x >= 0)
    {
        do
        {
            buffer[++len] = (x % 10) | 48;
            x /= 10;
        } while (x);
    }
    else
    {
        pc('-');
        do
        {
            buffer[++len] = -(x % 10) | 48;
            x /= 10;
        } while (x);
    }
    while (len >= 0)
        pc(buffer[len--]);
    return;
}
struct node
{
    int v;
    int w;
    int next;
} a[400005];
struct point
{
    int id;
    int d;
    point(int aa, int bb)
    {
        id = aa;
        d = bb;
    }
    inline bool operator<(const point &bb) const
    {
        return d > bb.d;
    }
};
priority_queue<point> q;
inline void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
int main()
{
  	n = read();
  	m = read();
  	p = read();
    for (register int i = 1; i <= p; ++i)
    {
        x[i] = read();
    	ans[x[i]] = 0x7f7f7f7f7f7f7f7f;
    }
    for (register int i = 1; i <= m; ++i)
    {
        int u, v, w;
      	u = read();
      	v = read();
      	w = read();
        ins(u, v, w);
        ins(v, u, w);
    }
    memset(d, 0x7f, sizeof(d));
    for (register int i = 1; i <= p; ++i)
    {
        fa[x[i]] = x[i];
        d[x[i]] = 0;
        q.push(point(x[i], 0));
    }
    while (!q.empty())
    {
        point kk = q.top();
        q.pop();
        int id = kk.id;
        if (vis[id])
            continue;
        vis[id] = 1;
        int dd = head[id];
        while (dd)
        {
            if (d[a[dd].v] > d[id] + a[dd].w)
            {
                d[a[dd].v] = d[id] + a[dd].w;
                fa[a[dd].v] = fa[id];
                q.push(point(a[dd].v, d[a[dd].v]));
            }
            dd = a[dd].next;
        }
    }
    for (register int i = 2; i <= 2 * m; i += 2)
        if (fa[a[i].v] != fa[a[i ^ 1].v])
        {
            if (ans[fa[a[i].v]] > d[a[i].v] + d[a[i ^ 1].v] + a[i].w)
                ans[fa[a[i].v]] = d[a[i].v] + d[a[i ^ 1].v] + a[i].w;
            if (ans[fa[a[i ^ 1].v]] > d[a[i].v] + d[a[i ^ 1].v] + a[i].w)
                ans[fa[a[i ^ 1].v]] = d[a[i].v] + d[a[i ^ 1].v] + a[i].w;
        }
    for (register int i = 1; i <= p; ++i)
    {
		write(ans[x[i]]);
  		pc(' ');
	}
  	flush();
    return 0;
}
