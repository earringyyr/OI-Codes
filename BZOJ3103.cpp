#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, pos, maxn = -1, sum, ans = 1;
int fa[1000005], head[1000005], label[1000005], vis[1000005], len[2000005];
char s[1000005], S[2000005];
struct node
{
    int v;
    int nxt;
} a[4000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        S[2 * i - 2] = '#';
        S[2 * i - 1] = s[i];
    }
    S[2 * n] = '#';
    n = 2 * n + 1;
    for (int i = 0; i < n; ++i)
    {
        if (i > maxn)
            len[i] = 1;
        else
            len[i] = min(len[2 * pos - i], maxn - i + 1);
        while (i - len[i] >= 0 && i + len[i] < n && S[i + len[i]] == S[i - len[i]])
        {
            ++len[i];
            if ((i + len[i] - 1) % 2 == 1)
            {
                int u = getfather((i + len[i]) / 2), v = getfather((i - len[i] + 2) / 2);
                if (u != v)
                    fa[u] = v;
            }
        }
        if (i + len[i] - 1 > maxn)
        {
            maxn = i + len[i] - 1;
            pos = i;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        int u = (i - len[i] + 1) / 2, v = (i + len[i] + 1) / 2;
        if (u >= 1 && v <= n / 2)
        {
            u = getfather(u);
            v = getfather(v);
            if (u != v)
            {
                ins(u, v);
                ins(v, u);
            }
        }
    }
    n /= 2;
    for (int i = 1; i <= n; ++i)
        if (getfather(i) == i)
        {
            ans = (ll)ans * (26 - label[i]) % mod;
            int d = head[i];
            while (d)
            {
                if (vis[a[d].v] != i)
                {
                    ++label[a[d].v];
                    vis[a[d].v] = i;
                }
                d = a[d].nxt;
            }
        }
    printf("%d", ans);
    return 0;
}