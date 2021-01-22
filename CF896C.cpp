#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
int n, m, ret, seed, v;
struct node
{
    int l;
    int r;
    mutable ll num;
    node(int aa = 0, int bb = 0, ll cc = 0)
    {
        l = aa;
        r = bb;
        num = cc;
    }
    bool operator<(const node &bb) const
    {
        return l < bb.l;
    }
};
set<node> s;
typedef set<node>::iterator iter;
int rnd()
{
    ret = seed;
    seed = ((ll)seed * 7 + 13) % 1000000007;
    return ret;
}
iter split(int pos)
{
    iter it = s.lower_bound(node(pos));
    if (it != s.end() && (*it).l == pos)
        return it;
    --it;
    int l = (*it).l, r = (*it).r;
    ll num = (*it).num;
    s.erase(it);
    s.insert(node(l, pos - 1, num));
    return s.insert(node(pos, r, num)).first;
}
void assign(int l, int r, int num)
{
    iter itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, num));
    return;
}
void add(int l, int r, int num)
{
    iter itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl)
        (*itl).num += num;
    return;
}
ll rnk(int l, int r, int k)
{
    vector<pair<ll, int> > vec;
    iter itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl)
        vec.push_back(make_pair((*itl).num, (*itl).r - (*itl).l + 1));
    sort(vec.begin(), vec.end());
    int siz = vec.size();
    for (int i = 0; i < siz; ++i)
    {
        k -= vec[i].second;
        if (k <= 0)
            return vec[i].first;
    }
    return 0;
}
int ksm(int aa, int k, int mod)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int sum(int l, int r, int x, int y)
{
    int ans = 0;
    iter itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl)
        ans = (ans + (ll)ksm((*itl).num % y, x, y) * ((*itl).r - (*itl).l + 1) % y) % y;
    return ans;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &seed, &v);
    for (int i = 1; i <= n; ++i)
        s.insert(node(i, i, (rnd() % v) + 1));
    for (int i = 1; i <= m; ++i)
    {
        int op, l, r, x, y;
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r)
            swap(l, r);
        if (op == 3)
            x = (rnd() % (r - l + 1)) + 1;
        else
            x = (rnd() % v) + 1;
        if (op == 4)
            y = (rnd() % v) + 1;
        if (op == 1)
            add(l, r, x);
        else if (op == 2)
            assign(l, r, x);
        else if (op == 3)
            printf("%lld\n", rnk(l, r, x));
        else
            printf("%d\n", sum(l, r, x, y));
    }
    return 0;
}