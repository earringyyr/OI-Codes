#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mod = 1000000000;
int m, Q, type, head, tail;
int t[100005];
int top[2], st[2][100005];
ll ans;
ll q[1005];
ll w[100005], v[100005];
ll f[505], ff[505], g[100005][505];
void reset(ll *a)
{
    a[0] = 0;
    for (int i = 1; i <= 500; ++i)
        a[i] = -inf;
    return;
}
void merge(ll *a, ll *b, int lef, int rig)
{
    head = 1;
    tail = 0;
    for (int i = rig; i >= lef; --i)
    {
        while (head <= tail && b[q[tail]] <= b[i])
            --tail;
        q[++tail] = i;
    }
    for (int i = 0; i < m; ++i)
    {
        ans = max(ans, a[i] + b[q[head]]);
        if (q[head] == (rig - i + m) % m)
            ++head;
        while (head <= tail && b[q[tail]] <= b[(lef - i - 1 + m) % m])
            --tail;
        q[++tail] = (lef - i - 1 + m) % m;
    }
    return;
}
int main()
{
    reset(f);
    for (int i = 0; i <= 100000; ++i)
        reset(g[i]);
    scanf("%d%d", &m, &type);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        int l, r;
        scanf("%d%lld%lld%d%d", &t[i], &w[i], &v[i], &l, &r);
        if (type == 1)
        {
            w[i] = w[i] ^ ans;
            v[i] = v[i] ^ ans;
            l = (l ^ ans) % m;
            r = (r ^ ans) % m;
        }
        if (l > r)
            swap(l, r);
        if (t[i] == 1)
        {
            swap(f, ff);
            for (int j = 0; j < m; ++j)
                f[(j + w[i]) % m] = max(ff[(j + w[i]) % m], ff[j] + v[i]);
            st[0][++top[0]] = i;
            ans = -inf;
            if (!top[1])
            {
                for (int j = l; j <= r; ++j)
                    ans = max(ans, f[j]);
                if (ans < 0)
                {
                    ans = -1;
                    puts("-1");
                }
                else
                    printf("%lld\n", ans);
            }
            else
            {
                merge(g[st[1][top[1]]], f, l, r);
                if (ans < 0)
                {
                    ans = -1;
                    puts("-1");
                }
                else
                    printf("%lld\n", ans);
            }
        }
        else
        {
            if (!top[0] && !top[1])
            {
                ans = 0;
                puts("-1");
                continue;
            }
            if (!top[1])
            {
                for (int j = top[0]; j >= 1; --j)
                    st[1][top[0] - j + 1] = st[0][j];
                reset(f);
                f[0] = 0;
                top[1] = top[0];
                top[0] = 0;
                for (int j = 1; j <= top[1]; ++j)
                    for (int k = 0; k < m; ++k)
                        g[st[1][j]][(k + w[st[1][j]]) % m] = max(g[st[1][j - 1]][(k + w[st[1][j]]) % m], g[st[1][j - 1]][k] + v[st[1][j]]);
            }
            --top[1];
            ans = -inf;
            if (!top[0])
            {
                for (int j = l; j <= r; ++j)
                    ans = max(ans, g[st[1][top[1]]][j]);
                if (ans < 0)
                {
                    ans = -1;
                    puts("-1");
                }
                else
                    printf("%lld\n", ans);
            }
            else
            {
                merge(g[st[1][top[1]]], f, l, r);
                if (ans < 0)
                {
                    ans = -1;
                    puts("-1");
                }
                else
                    printf("%lld\n", ans);
            }
        }
        ans = max(0LL, ans) % mod;
    }
    return 0;
}