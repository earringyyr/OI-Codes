#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
#define int long long
using namespace std;
int n, q, opt, ans, sum;
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int l;
    int r;
    int C;
    int L;
    int R;
    int LR;
    int siz;
} tr[2000005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].siz = 1;
    tr[id].L = 2 * l + 1;
    tr[id].R = 2 * r - 1;
    tr[id].C -= l * (l + 1) + r * (r - 1);
    if (l == r)
        return;
    tr[id].C += 4 * (l + 1) * (r - 1);
    tr[id].LR = 4;
    tr[id].L -= 4 * (r - 1);
    tr[id].R -= 4 * (l + 1);
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].siz += tr[lch].siz + tr[rch].siz;
    tr[id].C += tr[lch].C + tr[rch].C;
    tr[id].LR += tr[lch].LR + tr[rch].LR;
    tr[id].L += tr[lch].L + tr[rch].L;
    tr[id].R += tr[lch].R + tr[rch].R;
    return;
}
int solve(int id, int l, int r)
{
    if (l <= tr[id].l && tr[id].r <= r)
        return tr[id].C + (sum - l * l - r * r) * tr[id].siz + tr[id].L * l + tr[id].R * r + tr[id].LR * l * r;
    int tmp = sum;
    if (l <= tr[id].l)
        tmp -= (tr[id].l - l) * (tr[id].l - l + 1);
    if (tr[id].r <= r)
        tmp -= (r - tr[id].r) * (r - tr[id].r + 1);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (l <= mid)
        tmp += solve(lch, l, r);
    if (r >= mid + 1)
        tmp += solve(rch, l, r);
    return tmp;
}
signed main()
{
    scanf("%lld%lld%lld", &n, &q, &opt);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        scanf("%lld%lld", &l, &r);
        int a = (l ^ (ans * opt)) % n + 1;
        int b = (r ^ (ans * opt)) % n + 1;
        l = min(a, b);
        r = max(a, b);
        sum = (r - l + 1) * (r - l + 2);
        ans = solve(1, l, r) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}