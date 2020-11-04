#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> B[200005], G[200005];
int gcd(int a, int b)
{
    if (!b)
        return a;
    return gcd(b, a % b);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int d = gcd(n, m);
    int tmp, lenb, leng;
    scanf("%d", &lenb);
    for (int i = 1; i <= lenb; ++i)
    {
        scanf("%d", &tmp);
        B[tmp % d].push_back(tmp / d);
    }
    scanf("%d", &leng);
    for (int i = 1; i <= leng; ++i)
    {
        scanf("%d", &tmp);
        G[tmp % d].push_back(tmp / d);
    }
    if (d > lenb + leng)
    {
        printf("No");
        return 0;
    }
    for (int i = 0; i < d; ++i)
    {
        if (!B[i].size() && !G[i].size())
        {
            printf("No");
            return 0;
        }
    }
    printf("Yes");
    return 0;
}