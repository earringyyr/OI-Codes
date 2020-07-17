#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, kk, a[100];
char s[100];
struct node
{
    int a[100];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator+(const node &bb)
    {
        int len = max(a[0], bb.a[0]);
        node ans;
        ans.a[0] = len;
        for (int i = 1; i <= len; ++i)
        {
            ans.a[i] = a[i] + bb.a[i];
            ans.a[i + 1] += ans.a[i] / 10;
            ans.a[i] %= 10;
        }
        if (ans.a[len + 1] == 1)
            ++ans.a[0];
        return ans;
    }
    node operator-(const node &bb)
    {
        int len = max(a[0], bb.a[0]);
        node ans;
        ans.a[0] = len;
        for (int i = 1; i <= len; ++i)
        {
            ans.a[i] = a[i] - bb.a[i];
            ans.a[i + 1] += ans.a[i] / 10;
            ans.a[i] %= 10;
        }
        while (ans.a[ans.a[0]] == 0)
            --ans.a[0];
        return ans;
    }
    node operator*(const node &bb) const
    {
        int len = a[0] + bb.a[0];
        node ans;
        for (int i = 1; i <= a[0]; ++i)
            for (int j = 1; j <= bb.a[0]; ++j)
            {
                ans.a[i + j - 1] += a[i] * bb.a[j];
                ans.a[i + j] += ans.a[i + j - 1] / 10;
                ans.a[i + j - 1] %= 10;
            }
        ans.a[0] = len;
        while (ans.a[ans.a[0]] == 0)
            --ans.a[0];
        return ans;
    }
    bool operator<(const node &bb) const
    {
        if (a[0] != bb.a[0])
            return a[0] < bb.a[0];
        for (int i = a[0]; i >= 1; --i)
            if (a[i] != bb.a[i])
                return a[i] < bb.a[i];
    }
} f[100][10], num[100];
int main()
{
    scanf("%d%d%s", &n, &kk, s);
    for (int i = 0; i < n; ++i)
        a[i + 1] = s[i] - '0';
    for (int i = 1; i <= n; ++i)
    {
        int tem = a[i];
        while (tem > 0)
        {
            num[i].a[++num[i].a[0]] = tem % 10;
            tem /= 10;
        }
    }
    f[0][0].a[0] = 1;
    f[0][0].a[1] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= min(kk + 1, i); ++j)
        {
            node cnt, ten, tot;
            tot.a[0] = 1;
            tot.a[1] = 1;
            ten.a[0] = 2;
            ten.a[1] = 0;
            ten.a[2] = 1;
            for (int k = i - 1; k >= 0; --k)
            {
                cnt = num[k + 1] * tot + cnt;
                tot = tot * ten;
                f[i][j] = max(f[i][j], f[k][j - 1] * cnt);
            }
        }
    for (int i = f[n][kk + 1].a[0]; i >= 1; --i)
        printf("%d", f[n][kk + 1].a[i]);
    return 0;
}