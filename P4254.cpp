#include <iostream>
#include <cstdio>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, ans, cnt;
double k[100005], b[100005];
struct tree
{
    int l;
    int r;
    int top;
} tr[200005];
void build(int id, int l, int r)
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
void insert(int id, int x, int ll, int rr)
{
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (tr[id].l == ll && tr[id].r == rr)
    {
        int l = tr[id].l, r = tr[id].r;
        bool t1 = k[x] * l + b[x] > k[tr[id].top] * l + b[tr[id].top];
        bool t2 = k[x] * r + b[x] > k[tr[id].top] * r + b[tr[id].top];
        if (t1 && t2)
        {
            tr[id].top = x;
            return;
        }
        if (!t1 && !t2)
            return;
        bool t3 = tr[id].top == 0 || k[x] * mid + b[x] > k[tr[id].top] * mid + b[tr[id].top];
        if (t3)
        {
            if (t1)
                insert(rch, tr[id].top, mid + 1, rr);
            if (t2)
                insert(lch, tr[id].top, ll, mid);
            tr[id].top = x;
        }
        if (t1 && !t3)
            insert(lch, x, ll, mid);
        if (!t1 & !t3)
            insert(rch, x, mid + 1, rr);
        return;
    }
    if (rr <= mid)
        insert(lch, x, ll, rr);
    if (ll >= mid + 1)
        insert(rch, x, ll, rr);
    if (ll <= mid && rr >= mid + 1)
    {
        insert(lch, x, ll, mid);
        insert(rch, x, mid + 1, rr);
    }
    return;
}
void query(int id, int w)
{
    if (k[tr[id].top] * w + b[tr[id].top] > k[ans] * w + b[ans] || (k[tr[id].top] * w + b[tr[id].top] == k[ans] * w + b[ans] && tr[id].top < ans))
        ans = tr[id].top;
    if (tr[id].l == tr[id].r)
        return;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        query(lch, w);
    else
        query(rch, w);
    return;
}
int main()
{
    scanf("%d", &n);
    build(1, 1, 50000);
    for (int i = 1; i <= n; ++i)
    {
        string type;
        cin >> type;
        if (type == "Query")
        {
            int kk;
            scanf("%d", &kk);
            ans = 0;
            query(1, kk);
            printf("%d\n", (int)(k[ans] * kk + b[ans]) / 100);
        }
        else
        {
            ++cnt;
            scanf("%lf%lf", &b[cnt], &k[cnt]);
            b[cnt] -= k[cnt];
            insert(1, cnt, 1, 50000);
        }
    }
    return 0;
}