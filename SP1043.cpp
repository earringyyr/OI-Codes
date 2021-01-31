#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, m, num = 1, sum, tot;
int a[50005];
int pos[100005];
int lg[200005];
int p[20][100005], q[20][100005];
void build(int id, int l, int r, int dep)
{
    if (l == r)
    {
        pos[l] = id;
        return;
    }
    int mid = (l + r) >> 1;
    sum = a[mid];
    tot = max(0, a[mid]);
    p[dep][mid] = a[mid];
    q[dep][mid] = a[mid];
    for (int i = mid - 1; i >= l; --i)
    {
        sum += a[i];
        tot += a[i];
        p[dep][i] = max(p[dep][i + 1], tot);
        q[dep][i] = max(q[dep][i + 1], sum);
        tot = max(0, tot);
    }
    sum = a[mid + 1];
    tot = max(0, a[mid + 1]);
    p[dep][mid + 1] = a[mid + 1];
    q[dep][mid + 1] = a[mid + 1];
    for (int i = mid + 2; i <= r; ++i)
    {
        sum += a[i];
        tot += a[i];
        p[dep][i] = max(p[dep][i - 1], tot);
        q[dep][i] = max(q[dep][i - 1], sum);
        tot = max(0, tot);
    }
    build(lch, l, mid, dep + 1);
    build(rch, mid + 1, r, dep + 1);
    return;
}
int ask(int l, int r)
{
    if (l == r)
        return a[l];
    int dep = lg[pos[l]] - lg[pos[l] ^ pos[r]];
    return max(max(p[dep][l], p[dep][r]), q[dep][l] + q[dep][r]);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    while (num < n)
        num <<= 1;
    for (int i = 2; i <= (num << 1); ++i)
        lg[i] = lg[i >> 1] + 1;
    build(1, 1, num, 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", ask(l, r));
    }
    return 0;
}