#include <iostream>
#include <cstdio>
using namespace std;
int a, c, k, m, n, ans, tot, num[20], s[100005], lg[1000005], nxt[1000005][20], ha[1000005][20];
void read()
{
    int len = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        s[++len] = c ^ 48;
        c = getchar();
    }
    return;
}
int calc(int z)
{
    return (((long long)a * z + c) / k) % m;
}
bool check(int z)
{
    int cnt = 0, reg = n;
    for (int i = lg[n]; i >= 0; --i)
        if (reg >= (1 << i))
        {
            reg -= (1 << i);
            cnt = cnt * num[i] + ha[z][i];
            z = nxt[z][i];
        }
    return cnt == ans;
}
int main()
{
    scanf("%d%d%d%d%d", &a, &c, &k, &m, &n);
    read();
    lg[1] = 0;
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    num[0] = 959;
    for (int i = 1; i <= lg[n]; ++i)
        num[i] = num[i - 1] * num[i - 1];
    for (int i = 0; i < m; ++i)
    {
        nxt[i][0] = calc(i);
        ha[i][0] = (nxt[i][0] >= (m / 2));
    }
    for (int i = 1; i <= n; ++i)
        ans = ans * 959 + s[i];
    for (int i = 1; i <= lg[n]; ++i)
        for (int j = 0; j < m; ++j)
        {
            nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
            ha[j][i] = ha[j][i - 1] * num[i - 1] + ha[nxt[j][i - 1]][i - 1];
        }
    for (int i = 0; i < m; ++i)
        if (check(i))
            ++tot;
    printf("%d", tot);
    return 0;
}