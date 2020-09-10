#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
int D, S, T, cnt, ans;
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
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
    int operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} now, d[3005], s[3005], t[6005];
bool cmp(node aa, node bb)
{
    return atan2(aa.y - now.y, aa.x - now.x) < atan2(bb.y - now.y, bb.x - now.x);
}
signed main()
{
    scanf("%lld", &D);
    for (int i = 1; i <= D; ++i)
        scanf("%lld%lld", &d[i].x, &d[i].y);
    scanf("%lld", &S);
    for (int i = 1; i <= S; ++i)
        scanf("%lld%lld", &s[i].x, &s[i].y);
    scanf("%lld", &T);
    for (int i = 1; i <= T; ++i)
        scanf("%lld%lld", &t[i].x, &t[i].y);
    for (int i = 1; i <= S; ++i)
    {
        cnt = 0;
        now = s[i];
        sort(d + 1, d + D + 1, cmp);
        sort(t + 1, t + T + 1, cmp);
        for (int j = 1; j < T; ++j)
            t[j + T] = t[j];
        int pos = 0, l = 1, r = 1;
        for (int j = 1; j <= T; ++j)
        {
            while (l <= D && (t[j] - now).y >= 0 && ((d[l] - now) ^ (t[j] - now)) > 0)
            {
                ++l;
                cnt -= pos - (j - 1);
            }
            pos = max(pos, j);
            while (pos - j + 1 < T && ((t[j] - now) ^ (t[pos + 1] - now)) > 0)
            {
                ++pos;
                while (r <= D && ((t[j] - now).y >= 0 || (t[pos] - now).y >= 0) && (((t[j] - now).y >= 0 && (t[pos] - now).y <= 0) || ((d[r] - now) ^ (t[pos] - now)) > 0))
                    ++r;
                cnt += r - l;
            }
            ans += cnt;
        }
    }
    printf("%lld", ans);
    return 0;
}