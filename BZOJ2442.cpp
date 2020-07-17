#include <iostream>
#include <cstdio>
using namespace std;
struct node
{
    int id;
    long long f;
    long long sum;
} l[100005];
int n, k, head = 1, tail, e[100005];
long long sum[100005], f[100005];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &e[i]);
        sum[i] = sum[i - 1] + e[i];
    }
    for (int i = 1; i <= k; ++i)
    {
        while (head <= tail && l[tail].f - l[tail].sum <= f[i - 1] - sum[i])
            --tail;
        f[i] = sum[i];
        ++tail;
        l[tail].id = i;
        l[tail].f = f[i - 1];
        l[tail].sum = sum[i];
    }
    for (int i = k + 1; i <= n; ++i)
    {
        while (head <= tail && i - l[head].id + 1 > k + 1)
            ++head;
        while (head <= tail && l[tail].f - l[tail].sum <= f[i - 1] - sum[i])
            --tail;
        ++tail;
        l[tail].id = i;
        l[tail].f = f[i - 1];
        l[tail].sum = sum[i];
        f[i] = l[head].f - l[head].sum + sum[i];
    }
    printf("%lld", f[n]);
    return 0;
}