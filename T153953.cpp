#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
int n, m, c, cnt;
int rt[100005], X[100005];
uint base = 2333, h[100005];
ll ans;
struct tree
{
    int l;
    int r;
    uint hsh;
} tr[5000005];
void modify(int y, int &x, int l, int r, int w)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == r)
    {
        tr[x].hsh = X[l] * base;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        modify(tr[y].l, tr[x].l, l, mid, w);
    else
        modify(tr[y].r, tr[x].r, mid + 1, r, w);
    tr[x].hsh = tr[tr[x].l].hsh * h[r - mid] + tr[tr[x].r].hsh;
    return;
}
int lcp(int x, int y, int l, int r)
{
    if (l == r)
    {
        if (tr[x].hsh == tr[y].hsh)
            return n + 1;
        return l;
    }
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].hsh != tr[tr[y].l].hsh)
        return lcp(tr[x].l, tr[y].l, l, mid);
    else
        return lcp(tr[x].r, tr[y].r, mid + 1, r);
}
bool cmp(int x, int y, int l, int r)
{
    if (l == r)
        return tr[x].hsh < tr[y].hsh;
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].hsh != tr[tr[y].l].hsh)
        return cmp(tr[x].l, tr[y].l, l, mid);
    else
        return cmp(tr[x].r, tr[y].r, mid + 1, r);
}
struct node
{
    int rt;
    node(int aa = 0)
    {
        rt = aa;
    }
    bool operator<(const node &bb) const
    {
        return cmp(rt, bb.rt, 1, n);
    }
};
set<node> s;
int main()
{
    scanf("%d%d", &n, &m);
    h[0] = 1;
    for (int i = 1; i <= n; ++i)
        h[i] = h[i - 1] * base;
    ans = n + 1;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &c);
        c = n - c;
        for (int j = c; j >= 1; --j)
        {
            if (X[j] == 0)
            {
                X[j] = 1;
                if (j == c)
                    modify(rt[i - 1], rt[i], 1, n, j);
                else
                    modify(rt[i], rt[i], 1, n, j);
                break;
            }
            X[j] = 0;
            if (j == c)
                modify(rt[i - 1], rt[i], 1, n, j);
            else
                modify(rt[i], rt[i], 1, n, j);
        }
        s.insert(node(rt[i]));
        set<node>::iterator pre, now, nxt;
        now = s.find(node(rt[i]));
        if (now != s.begin())
        {
            pre = --now;
            ++now;
            ans += n - (lcp((*pre).rt, (*now).rt, 1, n) - 1);
        }
        nxt = ++now;
        --now;
        if (nxt != s.end())
            ans += n - (lcp((*now).rt, (*nxt).rt, 1, n) - 1);
        if (now != s.begin() && nxt != s.end())
            ans -= n - (lcp((*pre).rt, (*nxt).rt, 1, n) - 1);
        printf("%lld\n", ans);
    }
    return 0;
}