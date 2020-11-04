#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, sum, head[2000005], A[2000005];
ll m;
struct node
{
    int v;
    int nxt;
} a[4000005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int main()
{
    int T;
    T = read();
    while (T--)
    {
        int id, maxn = 0;
        sum = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%lld", &n, &m);
        for (int i = 1; i <= n; ++i)
            A[i] = read();
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            u = read();
            v = read();
            ins(u, v);
            ins(v, u);
        }
        if (n == 1)
        {
            printf("1\n");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            if (A[i] > maxn)
            {
                id = i;
                maxn = A[i];
            }
        maxn = 0;
        int ans[2];
        ans[1] = id;
        int d = head[id];
        while (d)
        {
            if (A[a[d].v] > maxn)
            {
                id = a[d].v;
                maxn = A[a[d].v];
            }
            else if (A[a[d].v] == maxn && a[d].v < id)
                id = a[d].v;
            d = a[d].nxt;
        }
        ans[0] = id;
        m -= A[ans[1]] - maxn;
        if (m < 0)
            printf("%d\n", ans[1]);
        else
        {
            if (ans[0] > ans[1])
                swap(ans[0], ans[1]);
            if (m % 2 == 1)
                printf("%d\n", ans[1]);
            else
                printf("%d\n", ans[0]);
        }
    }
    return 0;
}