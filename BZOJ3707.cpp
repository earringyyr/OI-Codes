#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const double eps = 1e-8;
int n, m, pos[1005], id[1005];
ll ans = 1e18;
struct node
{
    ll x;
    ll y;
    node(ll xx = 0, ll yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb)
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb)
    {
        return node(x - bb.x, y - bb.y);
    }
    ll operator*(const node &bb)
    {
        return x * bb.x + y * bb.y;
    }
    ll operator^(const node &bb)
    {
        return x * bb.y - y * bb.x;
    }
} p[1005];
struct line
{
    int a;
    int b;
    double k;
    line() {}
    line(int aa, int bb)
    {
        a = aa;
        b = bb;
        if (p[aa].x == p[bb].x)
            k = 1e18;
        else
            k = (double)(p[aa].y - p[bb].y) / (p[aa].x - p[bb].x);
    }
} l[1000005];
bool comp(node aa, node bb)
{
    if (aa.x != bb.x)
        return aa.x < bb.x;
    return aa.y < bb.y;
}
bool cmp(line aa, line bb)
{
    return aa.k < bb.k;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, comp);
    for (int i = 1; i <= n; ++i)
    {
        pos[i] = i;
        id[i] = i;
        for (int j = i + 1; j <= n; ++j)
            l[++m] = line(i, j);
    }
    sort(l + 1, l + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        int L = pos[l[i].a], R = pos[l[i].b];
        if (L > R)
            swap(L, R);
        if (L > 1)
            ans = min(ans, abs((p[id[L]] ^ p[id[R]]) + (p[id[R]] ^ p[id[L - 1]]) + (p[id[L - 1]] ^ p[id[L]])));
        if (R < n)
            ans = min(ans, abs((p[id[L]] ^ p[id[R]]) + (p[id[R]] ^ p[id[R + 1]]) + (p[id[R + 1]] ^ p[id[L]])));
        swap(id[L], id[R]);
        swap(pos[l[i].a], pos[l[i].b]);
    }
    double Ans = (double)ans / 2;
    printf("%.2f", Ans);
    return 0;
}