#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
int n, flg;
int s[100005];
int l[100005], r[100005], R[100005];
ll k;
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
struct tree
{
    int l;
    int r;
    int num;
    int flg;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].num = 0;
    tr[id].flg = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void add(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].num += val;
        if (tr[id].num > 0)
            tr[id].flg = 1;
        if (tr[id].num == 0)
            tr[id].flg = 0;
        if (tr[id].num < 0)
            tr[id].flg = -1;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    if (w >= mid + 1)
        add(rch, w, val);
    if (tr[lch].flg != 0)
        tr[id].flg = tr[lch].flg;
    else
        tr[id].flg = tr[rch].flg;
    return;
}
ll solve(int lef, int rig)
{
    ll num = 0;
    build(1, 1, n);
    for (int i = lef; i <= rig; ++i)
        add(1, s[i], 1);
    for (int i = 1; i <= n; ++i)
    {
        R[i] = max(R[i - 1], i - 1);
        while (R[i] < n)
        {
            add(1, s[R[i] + 1], -1);
            if (tr[1].flg > 0 || (tr[1].flg == 0 && i <= lef))
                ++R[i];
            else
            {
                add(1, s[R[i] + 1], 1);
                break;
            }
        }
        if (R[i] >= i)
            add(1, s[i], 1);
        num += R[i] - i + 1;
    }
    return num;
}
int main()
{
    srand(time(0));
    n = read();
    k = read();
    k = (ll)n * (n + 1) / 2 - k + 1;
    for (int i = 1; i <= n; ++i)
    {
        s[i] = read();
        l[i] = i;
        r[i] = n;
    }
    while (1)
    {
        int num = 0;
        for (int i = 1; i <= n; ++i)
            num += r[i] - l[i] + 1;
        int rnd = rand() % num + 1, lef, rig;
        for (int i = 1; i <= n; ++i)
            if (rnd <= r[i] - l[i] + 1)
            {
                lef = i;
                rig = l[i] + rnd - 1;
                break;
            }
            else
                rnd -= (r[i] - l[i] + 1);
        if (solve(lef, rig) >= k)
            for (int i = 1; i <= n; ++i)
                r[i] = R[i];
        else
            for (int i = 1; i <= n; ++i)
                l[i] = R[i] + 1;
        flg = 0;
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (l[i] <= r[i])
            {
                cnt += r[i] - l[i] + 1;
                if (l[i] == r[i])
                    flg = i;
            }
        if (cnt == 1 && flg)
            break;
    }
    sort(s + flg, s + r[flg] + 1);
    for (int i = flg; i <= r[flg]; ++i)
        printf("%d ", s[i]);
    return 0;
}