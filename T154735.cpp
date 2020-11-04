#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a, b, cnt = 1, sum;
struct edge
{
    int u;
    int v;
    edge(int aa = 0, int bb = 0)
    {
        u = aa;
        v = bb;
    }
} e[2005];
int main()
{
    scanf("%d%d", &a, &b);
    if (a == 0 && b == 0)
    {
        printf("1");
        return 0;
    }
    if (a < b + 2 || a == b + 3)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= b + 1; ++i)
        for (int j = 1; j <= 2; ++j)
        {
            ++cnt;
            e[++sum] = edge(i, cnt);
        }
    for (int i = b + 3; i <= a; ++i)
        e[++sum] = edge(1, i + b + 1);
    printf("%d\n", sum + 1);
    for (int i = 1; i <= sum; ++i)
        printf("%d %d\n", e[i].u, e[i].v);
    return 0;
}