#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, k, top, ans;
int x[200005];
int pre[200005], nxt[200005];
vector<int> h[200005], t[200005];
struct node
{
    int id;
    int x;
} a[200005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &x[i]);
        a[i].id = i;
        a[i].x = x[i];
        pre[i] = i - 1;
        nxt[i] = i + 1;
        h[i].assign(k + 5, 0);
        t[i].assign(k + 5, 0);
    }
    pre[0] = 0;
    nxt[0] = 1;
    pre[n + 1] = n;
    nxt[n + 1] = n + 1;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        int id;
        id = a[i].id;
        for (int j = 0; j <= k; ++j)
        {
            h[a[i].id][j] = id;
            id = pre[id];
        }
        id = a[i].id;
        for (int j = 0; j <= k; ++j)
        {
            t[a[i].id][j] = id;
            id = nxt[id];
        }
        nxt[pre[a[i].id]] = nxt[a[i].id];
        pre[nxt[a[i].id]] = pre[a[i].id];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < k; ++j)
            ans = (ans + (ll)(h[i][j] - h[i][j + 1]) * (t[i][k - j] - i) % mod * x[i] % mod) % mod;
    printf("%d", ans);
    return 0;
}