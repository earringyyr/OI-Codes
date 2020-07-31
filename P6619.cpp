#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
using namespace std;
int Q, num;
int type[2000005], t[2000005], x[2000005], y[2000005], k[2000005];
int b[2000005];
namespace io_in
{
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    inline int read()
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
    inline void flush()
    {
        fwrite(buf, 1, p1 + 1, stdout);
        p1 = -1;
        return;
    }
    inline void pc(char x)
    {
        if (p1 == p2)
            flush();
        buf[++p1] = x;
        return;
    }
    inline void write(int x)
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
struct tree
{
    int l;
    int r;
    int sum;
    int num[2];
    int lazy[2];
} tr[8000005];
int twofen(int l, int r, int val)
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (b[mid] >= val)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
inline void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
inline void pushdown(int id)
{
    if (tr[id].l != tr[id].r && (tr[id].lazy[0] || tr[id].lazy[1]))
    {
        tr[lch].lazy[0] += tr[id].lazy[0];
        tr[rch].lazy[0] += tr[id].lazy[0];
        tr[lch].lazy[1] += tr[id].lazy[1];
        tr[rch].lazy[1] += tr[id].lazy[1];
        tr[lch].num[0] += tr[id].lazy[0];
        tr[rch].num[0] += tr[id].lazy[0];
        tr[lch].num[1] += tr[id].lazy[1];
        tr[rch].num[1] += tr[id].lazy[1];
        tr[lch].sum += tr[id].lazy[1] - tr[id].lazy[0];
        tr[rch].sum += tr[id].lazy[1] - tr[id].lazy[0];
        tr[id].lazy[0] = 0;
        tr[id].lazy[1] = 0;
    }
    return;
}
inline void add(int id, int l, int r, int w, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num[w] += val;
        tr[id].lazy[w] += val;
        if (w == 0)
            tr[id].sum -= val;
        else
            tr[id].sum += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, w, val);
    if (l >= mid + 1)
        add(rch, l, r, w, val);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, w, val);
        add(rch, mid + 1, r, w, val);
    }
    tr[id].num[0] = max(tr[lch].num[0], tr[rch].num[0]);
    tr[id].num[1] = max(tr[lch].num[1], tr[rch].num[1]);
    tr[id].sum = max(tr[lch].sum, tr[rch].sum);
    return;
}
inline int query(int id)
{
    pushdown(id);
    if (tr[id].sum <= 0)
        return 0;
    if (tr[id].l == tr[id].r)
        return tr[id].l;
    if (tr[rch].sum > 0)
        return query(rch);
    return query(lch);
}
inline int ask(int id, int w)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return min(tr[id].num[0], tr[id].num[1]);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        return ask(lch, w);
    else
        return ask(rch, w);
}
inline int qiu(int id, int val)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].l;
    if (tr[rch].num[1] >= val)
        return qiu(rch, val);
    else
        return qiu(lch, val);
}
int main()
{
    Q = io_in::read();
    for (register int i = 1; i <= Q; ++i)
    {
        type[i] = io_in::read();
        if (type[i] == 1)
        {
            t[i] = io_in::read();
            x[i] = io_in::read();
            y[i] = io_in::read();
            b[++num] = x[i];
        }
        if (type[i] == 2)
            k[i] = io_in::read();
    }
    sort(b + 1, b + num + 1);
    int len = unique(b + 1, b + num + 1) - b - 1;
    build(1, 1, len);
    for (register int i = 1; i <= Q; ++i)
    {
        if (type[i] == 1)
        {
            x[i] = twofen(1, len, x[i]);
            if (t[i] == 0)
                add(1, x[i], len, t[i], y[i]);
            else
                add(1, 1, x[i], t[i], y[i]);
        }
        else
        {
            if (t[k[i]] == 0)
                add(1, x[k[i]], len, t[k[i]], -y[k[i]]);
            else
                add(1, 1, x[k[i]], t[k[i]], -y[k[i]]);
        }
        int l = query(1);
        int r = l + 1, ans = 0, pos = l, ans1 = 0, ans2 = 0;
        if (l >= 1 && l <= len)
            ans = ask(1, l);
        if (r >= 1 && r <= len)
        {
            int tmp = ask(1, r);
            if (ans <= tmp)
            {
                ans = tmp;
                pos = r;
            }
        }
        if (!ans)
        {
            io_out::pc('P');
            io_out::pc('e');
            io_out::pc('a');
            io_out::pc('c');
            io_out::pc('e');
            io_out::pc('\n');
        }
        else
        {
            if (pos == r)
                pos = qiu(1, ans);
            ans <<= 1;
            io_out::write(b[pos]);
            io_out::pc(' ');
            io_out::write(ans);
            io_out::pc('\n');
        }
    }
    io_out::flush();
    return 0;
}