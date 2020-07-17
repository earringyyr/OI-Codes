#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, m;
long long a[100005];
struct node
{
    int l;
    int r;
    long long sum;
} tr[400005];
void change(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        if (tr[id].sum == tr[id].r - tr[id].l + 1)
            return;
        if (tr[id].l == tr[id].r)
        {
            tr[id].sum = sqrt(tr[id].sum);
            return;
        }
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change(lch, l, r);
    if (l >= mid + 1)
        change(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        change(lch, l, mid);
        change(rch, mid + 1, r);
    }
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
long long ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return ask(lch, l, mid) + ask(rch, mid + 1, r);
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (tr[id].l == tr[id].r)
    {
        tr[id].sum = a[l];
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        int k, l, r;
        cin >> k >> l >> r;
        if (l > r)
            swap(l, r);
        if (!k)
            change(1, l, r);
        if (k)
            cout << ask(1, l, r) << endl;
    }
    return 0;
}