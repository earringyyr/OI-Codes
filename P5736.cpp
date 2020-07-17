#include <iostream>
#include <cstdio>
int n, sum, num[100005], v[100005];
void xxs()
{
    for (int i = 2; i <= 100000; ++i)
    {
        if (!num[i])
        {
            num[i] = i;
            v[++sum] = i;
        }
        for (int j = 1; j <= sum && v[j] * i <= 100000 && v[j] <= num[i]; ++j)
            num[i * v[j]] = v[j];
    }
    return;
}
int main()
{
    xxs();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        if (num[x] == x)
            printf("%d ", x);
    }
    return 0;
}