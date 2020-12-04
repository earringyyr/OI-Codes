#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
namespace io_in
{
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    int read()
    {
        int x = 0, f = 1;
        char c = gc();
        while (!isdigit(c))
        {
            if (c == '-')
                f = -1;
            c = gc();
        }
        while (isdigit(c))
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = gc();
        }
        return x * f;
    }
} // namespace io_in
namespace io_out
{
    char buf[1 << 21];
    int p1 = -1;
    const int p2 = (1 << 21) - 1;
    void flush()
    {
        fwrite(buf, 1, p1 + 1, stdout);
        p1 = -1;
        return;
    }
    void pc(char x)
    {
        if (p1 == p2)
            flush();
        buf[++p1] = x;
        return;
    }
    void write(int x)
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
} // namespace io_out
using namespace io_in;
using namespace io_out;
typedef long long ll;
int n, rt, cnt, opt, len;
int d[100005], ans[100005];
struct node
{
    int id;
    int x[2];
    bool operator<(const node &bb) const
    {
        return x[opt] < bb.x[opt];
    }
} now, a[100005], b[100005], p[100005];
struct tree
{
    int id;
    int l;
    int r;
    int x;
    int X;
    int y;
    int Y;
    int num;
    int lazy;
} tr[100005];
inline int my_min(int x, int y)
{
    return x < y ? x : y;
}
inline int my_max(int x, int y)
{
    return x > y ? x : y;
}
inline int solve(int l, int r)
{
    double sum[2][2] = {0};
    for (int i = l; i <= r; ++i)
    {
        sum[0][0] += b[i].x[0];
        sum[0][1] += (ll)b[i].x[0] * b[i].x[0];
        sum[1][0] += b[i].x[1];
        sum[1][1] += (ll)b[i].x[1] * b[i].x[1];
    }
    return (r - l + 1) * sum[0][1] - sum[0][0] * sum[0][0] < (r - l + 1) * sum[1][1] - sum[1][0] * sum[1][0];
}
inline bool cmp(node aa, node bb)
{
    return aa.x[opt] < bb.x[opt];
}
void build(int &x, int l, int r)
{
    if (l > r)
        return;
    x = ++cnt;
    if (l == r)
    {
        tr[x].id = b[l].id;
        tr[x].x = b[l].x[0];
        tr[x].X = b[l].x[0];
        tr[x].y = b[l].x[1];
        tr[x].Y = b[l].x[1];
        p[x] = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    opt = solve(l, r);
    nth_element(b + l, b + mid, b + r + 1, cmp);
    build(tr[x].l, l, mid - 1);
    build(tr[x].r, mid + 1, r);
    tr[x].id = b[mid].id;
    tr[x].x = b[mid].x[0];
    tr[x].X = b[mid].x[0];
    tr[x].y = b[mid].x[1];
    tr[x].Y = b[mid].x[1];
    p[x] = b[mid];
    if (tr[x].l)
    {
        tr[x].x = my_min(tr[x].x, tr[tr[x].l].x);
        tr[x].X = my_max(tr[x].X, tr[tr[x].l].X);
        tr[x].y = my_min(tr[x].y, tr[tr[x].l].y);
        tr[x].Y = my_max(tr[x].Y, tr[tr[x].l].Y);
    }
    if (tr[x].r)
    {
        tr[x].x = my_min(tr[x].x, tr[tr[x].r].x);
        tr[x].X = my_max(tr[x].X, tr[tr[x].r].X);
        tr[x].y = my_min(tr[x].y, tr[tr[x].r].y);
        tr[x].Y = my_max(tr[x].Y, tr[tr[x].r].Y);
    }
    return;
}
inline int dis(node aa, int x, int y)
{
    return abs(aa.x[0] - x) + abs(aa.x[1] - y);
}
void add(int x)
{
    if (dis(now, p[x].x[0], p[x].x[1]) <= len)
        ++tr[x].num;
    if (my_max(abs(now.x[0] - tr[x].x), abs(now.x[0] - tr[x].X)) + my_max(abs(now.x[1] - tr[x].y), abs(now.x[1] - tr[x].Y)) <= len)
    {
        ++tr[x].lazy;
        return;
    }
    if (tr[x].l)
    {
        if (dis(now, my_min(tr[tr[x].l].X, my_max(tr[tr[x].l].x, now.x[0])), my_min(tr[tr[x].l].Y, my_max(tr[tr[x].l].y, now.x[1]))) <= len)
            add(tr[x].l);
    }
    if (tr[x].r)
    {
        if (dis(now, my_min(tr[tr[x].r].X, my_max(tr[tr[x].r].x, now.x[0])), my_min(tr[tr[x].r].Y, my_max(tr[tr[x].r].y, now.x[1]))) <= len)
            add(tr[x].r);
    }
    return;
}
void dfs(int x)
{
    ans[tr[x].id] = tr[x].num - 1;
    if (tr[x].l)
    {
        tr[tr[x].l].num += tr[x].lazy;
        tr[tr[x].l].lazy += tr[x].lazy;
        dfs(tr[x].l);
    }
    if (tr[x].r)
    {
        tr[tr[x].r].num += tr[x].lazy;
        tr[tr[x].r].lazy += tr[x].lazy;
        dfs(tr[x].r);
    }
    return;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i].id = i;
        a[i].x[0] = read();
        a[i].x[1] = read();
        d[i] = read();
        b[i] = a[i];
    }
    build(rt, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        now = a[i];
        len = d[i];
        add(rt);
    }
    dfs(rt);
    for (int i = 1; i <= n; ++i)
    {
        write(ans[i]);
        pc(' ');
    }
    flush();
    return 0;
}