#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;
int n, m, q, num;
bitset<50005> s[10][2505], base, ans, Ans;
struct node
{
    int id;
    int num;
    bool operator<(const node &bb)
    {
        return num < bb.num;
    }
} a[10][50005];
int main()
{
    base[0] = 1;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        num = 0;
        for (int i = 1; i <= 5; ++i)
            s[i][0].reset();
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= 5; ++j)
            {
                a[j][i].id = i;
                scanf("%d", &a[j][i].num);
            }
        for (int i = 1; i <= 5; ++i)
        {
            sort(a[i] + 1, a[i] + n + 1);
            for (int j = 1; j <= n; ++j)
            {
                if (j % 25 == 0 && j != 1)
                    s[i][j / 25] = s[i][j / 25 - 1];
                s[i][j / 25][a[i][j].id] = 1;
            }
        }
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i)
        {
            Ans.set();
            for (int j = 1; j <= 5; ++j)
            {
                ans.reset();
                int x;
                scanf("%d", &x);
                x ^= num;
                int l = 1, r = n;
                while (l < r)
                {
                    int mid = (l + r + 1) >> 1;
                    if (a[j][mid].num <= x)
                        l = mid;
                    else
                        r = mid - 1;
                }
                if (l / 25 >= 1)
                    ans = s[j][l / 25 - 1];
                for (int k = l / 25 * 25; k <= l; ++k)
                    ans[a[j][k].id] = 1;
                Ans &= ans;
            }
            num = Ans.count();
            printf("%d\n", num);
        }
    }
    return 0;
}