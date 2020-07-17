#include <iostream>
#include <cstdio>
using namespace std;
int n, sum, head[200005], son[200005];
int w[200005];
long long ans_ma, ans;
struct node
{
    int v;
    int next;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    son[u]++;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
int main()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i <= n; ++i)
        if (son[i] >= 2)
        {
            int d = head[i], da = 0, daa = 0;
            long long val = 0, add = 0;
            while (d)
            {
                val += w[a[d].v];
                add += w[a[d].v] * w[a[d].v];
                if (w[a[d].v] > da)
                {
                    daa = da;
                    da = w[a[d].v];
                }
                else if (w[a[d].v] > daa)
                    daa = w[a[d].v];
                d = a[d].next;
            }
            if (da * daa > ans_ma)
                ans_ma = da * daa;
            ans = (ans + val * val - add) % 10007;
        }
    cout << ans_ma << " " << ans;
    return 0;
}