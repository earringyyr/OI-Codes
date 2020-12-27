#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, f[100005][15];
ll ans;
char s[100005];
int calc(int X, int y)
{
    int x = s[X] - '0';
    return (9 + (ll)y * (y - 1) / 2 + x + 1) % 11;
}
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] != '0')
            f[i][s[i] - '0'] = 1;
        for (int j = s[i] - '0' + 1; j < 11; ++j)
            f[i][calc(i, j)] += f[i - 1][j];
        for (int j = 0; j < 11; ++j)
            ans += f[i][j];
    }
    printf("%lld", ans);
    return 0;
}