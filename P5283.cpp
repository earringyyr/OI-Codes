#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define mp make_pair
using namespace std;
typedef unsigned int uint;
int n, k, cnt;
int top[500005], siz[20000005], tr[20000005][2];
uint a[500005];
long long ans;
priority_queue<pair<uint, int> > q;
void ins(uint x)
{
    int rt = 0;
    ++siz[rt];
    for (int i = 31; i >= 0; --i)
    {
        int k = (x & ((uint)1 << i)) ? 1 : 0;
        if (!tr[rt][k])
            tr[rt][k] = ++cnt;
        rt = tr[rt][k];
        ++siz[rt];
    }
    return;
}
uint query(uint x, int rk)
{
    uint y = 0;
    int rt = 0;
    if (rk > siz[0])
        return 0;
    for (int i = 31; i >= 0; --i)
    {
        int k = (x & ((uint)1 << i)) ? 0 : 1;
        if (tr[rt][k] && siz[tr[rt][k]] >= rk)
        {
            y += (uint)1 << i;
            rt = tr[rt][k];
        }
        else
        {
            if (tr[rt][k])
                rk -= siz[tr[rt][k]];
            rt = tr[rt][k ^ 1];
        }
    }
    return y;
}
int main()
{
    scanf("%d%d", &n, &k);
    ins(0);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%u", &a[i]);
        a[i] ^= a[i - 1];
        ins(a[i]);
    }
    for (int i = 0; i <= n; ++i)
        q.push(mp(query(a[i], ++top[i]), i));
    for (int i = 1; i <= 2 * k; ++i)
    {
        ans += q.top().first;
        int k = q.top().second;
        q.pop();
        q.push(mp(query(a[k], ++top[k]), k));
    }
    printf("%lld", ans / 2);
    return 0;
}