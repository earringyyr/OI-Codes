#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
#define inf 1e18
struct tree
{
    int l;
    int r;
    long long mx;
    long long sum;
} tr[100005 * 100];
struct node
{
    int id;
    long long sum;
    node(int aa = 0, long long bb = 0)
    {
        id = aa;
        sum = bb;
    }
    bool operator<(const node &bb) const
    {
        return sum < bb.sum;
    }
};
int n, k, cnt, a[100005], rt[100005];
priority_queue<node> q;
map<int, int> mp;
void pushup(int x)
{
    if (!tr[x].l)
        tr[x].mx = tr[tr[x].r].mx;
    else if (!tr[x].r)
        tr[x].mx = tr[tr[x].l].mx;
    else
        tr[x].mx = max(tr[tr[x].l].mx, tr[tr[x].r].mx);
    tr[x].mx += tr[x].sum;
    return;
}
void change(int y, int &x, int l, int r, int L, int R, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == L && r == R)
    {
        tr[x].sum += val;
        pushup(x);
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        change(tr[y].l, tr[x].l, l, mid, L, R, val);
    if (L >= mid + 1)
        change(tr[y].r, tr[x].r, mid + 1, r, L, R, val);
    if (L <= mid && R >= mid + 1)
    {
        change(tr[y].l, tr[x].l, l, mid, L, mid, val);
        change(tr[y].r, tr[x].r, mid + 1, r, mid + 1, R, val);
    }
    pushup(x);
    return;
}
void modify(int y, int &x, int l, int r)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == r)
    {
        tr[x].sum = -inf;
        pushup(x);
        return;
    }
    int mid = (l + r) >> 1;
    if (!tr[x].l)
        modify(tr[y].r, tr[x].r, mid + 1, r);
    else if (!tr[x].r)
        modify(tr[y].l, tr[x].l, l, mid);
    else
    {
        if (tr[tr[x].l].mx >= tr[tr[x].r].mx)
            modify(tr[y].l, tr[x].l, l, mid);
        else
            modify(tr[y].r, tr[x].r, mid + 1, r);
    }
    pushup(x);
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        change(rt[i - 1], rt[i], 1, n, i, i, 0);
        change(rt[i], rt[i], 1, n, mp[a[i]] + 1, i, a[i]);
        mp[a[i]] = i;
        q.push(node(i, tr[rt[i]].mx));
    }
    for (int i = 1; i < k; ++i)
    {
        int id = q.top().id;
        q.pop();
        modify(rt[id], rt[id], 1, n);
        q.push(node(id, tr[rt[id]].mx));
    }
    printf("%lld\n", q.top().sum);
    return 0;
}