#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ttt, n, m, ans, len, t[100005], f[100005];
struct node
{
    int w;
    int v;
} a[100005];
bool cmp(node aa, node bb)
{
    if (aa.w != bb.w)
        return aa.w < bb.w;
    return aa.v < bb.v;
}
int main()
{
    scanf("%d", &ttt);
    for (int tt = 1; tt <= ttt; ++tt)
    {
        ans = 0;
        len = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &a[i].w, &a[i].v);
        sort(a + 1, a + n + 1, cmp);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d", &t[i]);
        sort(t + 1, t + m + 1);
        f[0] = 1000000005;
        for (int i = n; i >= 1; --i)
        {
            if (a[i].v <= f[len])
            {
                int l = 1, r = m;
                while (l < r)
                {
                    int mid = (l + r) >> 1;
                    if (t[mid] < a[i].w)
                        l = mid + 1;
                    else
                        r = mid;
                }
                if (t[l] < a[i].w)
                    continue;
                ans = max(ans, min(len + 1, m - l + 1));
                if (len + 1 <= m - l + 1)
                    f[++len] = a[i].v;
                continue;
            }
            int l = 1, r = len;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (f[mid] < a[i].v)
                    r = mid;
                else
                    l = mid + 1;
            }
            int k = l;
            l = 1;
            r = m;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (t[mid] < a[i].w)
                    l = mid + 1;
                else
                    r = mid;
            }
            if (t[l] < a[i].w)
                continue;
            ans = max(ans, min(k, m - l + 1));
            if (k <= m - l + 1)
                f[k] = a[i].v;
        }
        printf("%d\n", ans);
    }
    return 0;
}