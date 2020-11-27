#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
using namespace std;
int n, m, ans;
int p[100005], b[100005];
struct node
{
    int id;
    int l;
    int r;
} a[100005];
struct Cmpl
{
    bool operator()(const node &aa, const node &bb) const
    {
        if (aa.l != bb.l)
            return aa.l < bb.l;
        return aa.r < bb.r;
    }
};
struct Cmpr
{
    bool operator()(const node &aa, const node &bb) const
    {
        if (aa.r != bb.r)
            return aa.r < bb.r;
        return aa.l < bb.l;
    }
};
struct CmpL
{
    bool operator()(const node &aa, const node &bb) const
    {
        if (aa.l != bb.l)
            return aa.l > bb.l;
        return aa.r > bb.r;
    }
};
struct CmpR
{
    bool operator()(const node &aa, const node &bb) const
    {
        if (aa.r != bb.r)
            return aa.r > bb.r;
        return aa.l > bb.l;
    }
};
set<int> id, tmp;
set<int, greater<int> > s;
vector<node> vec[100005];
multiset<node, Cmpl> L;
multiset<node, Cmpr> R;
priority_queue<node, vector<node>, CmpR> q[100005];
bool cmpl(node aa, node bb)
{
    return aa.l < bb.l;
}
bool cmpr(node aa, node bb)
{
    return aa.r < bb.r;
}
bool cmpL(node aa, node bb)
{
    return aa.l > bb.l;
}
bool cmpR(node aa, node bb)
{
    return aa.r > bb.r;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &a[i].l, &a[i].r, &p[i]);
        b[i] = p[i];
    }
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
    {
        p[i] = lower_bound(b + 1, b + len + 1, p[i]) - b;
        a[i].id = p[i];
        vec[p[i]].push_back(a[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!vec[i].empty())
        {
            int siz = vec[i].size();
            sort(vec[i].begin(), vec[i].end(), cmpR);
            int minx = vec[i][0].r + 1;
            for (int j = 0; j < siz; ++j)
            {
                minx = min(minx - 1, vec[i][j].r);
                s.insert(minx);
            }
            sort(vec[i].begin(), vec[i].end(), cmpL);
            for (int j = 0; j < siz; ++j)
            {
                set<int, greater<int> >::iterator it = s.lower_bound(vec[i][j].r);
                vec[i][j].r = *it;
                L.insert(vec[i][j]);
                R.insert(vec[i][j]);
                if (vec[i][j].l > vec[i][j].r)
                {
                    printf("GG");
                    return 0;
                }
                s.erase(it);
            }
            sort(vec[i].begin(), vec[i].end(), cmpl);
        }
    while (!R.empty())
    {
        ++ans;
        int r = (*R.begin()).r;
        while (!L.empty() && (*L.begin()).l <= r)
        {
            q[(*L.begin()).id].push(*L.begin());
            id.insert((*L.begin()).id);
            L.erase(L.begin());
        }
        while (!id.empty())
        {
            R.erase(R.find(q[*id.begin()].top()));
            q[*id.begin()].pop();
            if (!q[*id.begin()].empty())
                tmp.insert(*id.begin());
            id.erase(id.begin());
        }
        while (!tmp.empty())
        {
            id.insert(*tmp.begin());
            tmp.erase(tmp.begin());
        }
    }
    printf("%d", ans);
    return 0;
}