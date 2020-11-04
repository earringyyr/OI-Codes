#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
int pos[300005], minx[300005], maxn[300005];
int c[600005];
ll ans;
void solve(int l, int r)
{
    if (l == r)
    {
        ++ans;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    minx[mid] = pos[mid];
    maxn[mid] = pos[mid];
    for (int i = mid - 1; i >= l; --i)
    {
        minx[i] = min(minx[i + 1], pos[i]);
        maxn[i] = max(maxn[i + 1], pos[i]);
    }
    minx[mid + 1] = pos[mid + 1];
    maxn[mid + 1] = pos[mid + 1];
    for (int i = mid + 2; i <= r; ++i)
    {
        minx[i] = min(minx[i - 1], pos[i]);
        maxn[i] = max(maxn[i - 1], pos[i]);
    }
    for (int i = l; i <= mid; ++i)
    {
        int pos = i + maxn[i] - minx[i];
        if (pos >= mid + 1 && pos <= r)
            if (maxn[pos] <= maxn[i] && minx[pos] >= minx[i])
                ++ans;
    }
    for (int i = mid + 1; i <= r; ++i)
    {
        int pos = i - maxn[i] + minx[i];
        if (pos >= l && pos <= mid)
            if (maxn[pos] <= maxn[i] && minx[pos] >= minx[i])
                ++ans;
    }
    int i, j, k;
    for (i = mid, j = mid + 1, k = mid + 1; i >= l; --i)
    {
        while (j <= r && minx[j] >= minx[i])
        {
            ++c[maxn[j] - j + 300000];
            ++j;
        }
        while (k < j && k <= r && maxn[k] < maxn[i])
        {
            --c[maxn[k] - k + 300000];
            ++k;
        }
        ans += c[minx[i] - i + 300000];
    }
    while (k < j)
    {
        --c[maxn[k] - k + 300000];
        ++k;
    }
    for (i = mid, j = mid + 1, k = mid + 1; i >= l; --i)
    {
        while (j <= r && maxn[j] <= maxn[i])
        {
            ++c[minx[j] + j];
            ++j;
        }
        while (k < j && k <= r && minx[k] > minx[i])
        {
            --c[minx[k] + k];
            ++k;
        }
        ans += c[maxn[i] + i];
    }
    while (k < j)
    {
        --c[minx[k] + k];
        ++k;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        pos[x] = y;
    }
    solve(1, n);
    printf("%lld", ans);
    return 0;
}