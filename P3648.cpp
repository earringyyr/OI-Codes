#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, k, pos[205], top[205], a[100005], pre[100005][205];
ll ans;
struct node
{
    double x;
    double y;
    node(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
};
struct line
{
    int id;
    int b;
    ll a;
    line(int aa = 0, ll bb = 0)
    {
        a = bb;
        b = aa;
    }
} l[100005][205];
node intersect(line aa, line bb)
{
    node cc = node(0, aa.a - bb.a);
    double k = (node(1, bb.b) ^ cc) / (node(1, aa.b) ^ node(1, bb.b));
    cc = node(k, aa.b * k);
    return node(0, aa.a) + cc;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        a[i] += a[i - 1];
    }
    for (int i = 0; i <= k; ++i)
        pos[i] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = k; j >= 1; --j)
            if (top[j - 1])
            {
                while (pos[j - 1] < top[j - 1] && intersect(l[pos[j - 1]][j - 1], l[pos[j - 1] + 1][j - 1]).x <= a[i])
                    ++pos[j - 1];
                ll f = (ll)l[pos[j - 1]][j - 1].b * a[i] + l[pos[j - 1]][j - 1].a;
                pre[i][j] = l[pos[j - 1]][j - 1].id;
                if (i == n && j == k)
                    ans = f;
                line now = line(a[i], f - (ll)a[i] * a[i]);
                now.id = i;
                while (top[j] > 1 && ((intersect(l[top[j]][j], l[top[j] - 1][j]) - node(0, now.a)) ^ node(1, now.b)) >= 0)
                    --top[j];
                while (top[j] && now.b == l[top[j]][j].b)
                    --top[j];
                l[++top[j]][j] = now;
                if (top[j] < pos[j])
                    pos[j] = top[j];
            }
        line now = line(a[i], -(ll)a[i] * a[i]);
        now.id = i;
        while (top[0] > 1 && ((intersect(l[top[0]][0], l[top[0] - 1][0]) - node(0, now.a)) ^ node(1, now.b)) >= 0)
            --top[0];
        l[++top[0]][0] = now;
        if (top[0] < pos[0])
            pos[0] = top[0];
    }
    printf("%lld\n", ans);
    int j = n;
    for (int i = k; i >= 1; --i)
    {
        j = pre[j][i];
        printf("%d ", j);
    }
    return 0;
}