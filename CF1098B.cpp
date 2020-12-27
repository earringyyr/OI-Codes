#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, len = 1, Ans = 1e9;
int co[2][2];
char s[300005];
vector<int> a[300005], ans[300005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + len);
        len += strlen(s + len);
    }
    for (int i = 1; i <= n; ++i)
    {
        a[i].resize(m + 1);
        ans[i].resize(m + 1);
        for (int j = 1; j <= m; ++j)
        {
            char k = s[(i - 1) * m + j];
            if (k == 'A')
                a[i][j] = 1;
            else if (k == 'G')
                a[i][j] = 2;
            else if (k == 'C')
                a[i][j] = 3;
            else
                a[i][j] = 4;
        }
    }
    for (co[0][0] = 1; co[0][0] <= 4; ++co[0][0])
        for (co[0][1] = 1; co[0][1] <= 4; ++co[0][1])
            if (co[0][1] != co[0][0])
                for (co[1][0] = 1; co[1][0] <= 4; ++co[1][0])
                    if (co[1][0] != co[0][0] && co[1][0] != co[0][1])
                        for (co[1][1] = 1; co[1][1] <= 4; ++co[1][1])
                            if (co[1][1] != co[0][0] && co[1][1] != co[0][1] && co[1][1] != co[1][0])
                            {
                                int tmp = 0;
                                for (int i = 1; i <= n; ++i)
                                {
                                    int num1 = 0, num2 = 0;
                                    for (int j = 1; j <= m; ++j)
                                    {
                                        if (co[i % 2][j % 2] != a[i][j])
                                            ++num1;
                                        if (co[i % 2][(j % 2) ^ 1] != a[i][j])
                                            ++num2;
                                    }
                                    tmp += min(num1, num2);
                                }
                                if (tmp < Ans)
                                {
                                    for (int i = 1; i <= n; ++i)
                                    {
                                        int num1 = 0, num2 = 0;
                                        for (int j = 1; j <= m; ++j)
                                        {
                                            if (co[i % 2][j % 2] != a[i][j])
                                                ++num1;
                                            if (co[i % 2][(j % 2) ^ 1] != a[i][j])
                                                ++num2;
                                        }
                                        if (num1 < num2)
                                            for (int j = 1; j <= m; ++j)
                                                ans[i][j] = co[i % 2][j % 2];
                                        else
                                            for (int j = 1; j <= m; ++j)
                                                ans[i][j] = co[i % 2][(j % 2) ^ 1];
                                    }
                                    Ans = tmp;
                                }
                                tmp = 0;
                                for (int j = 1; j <= m; ++j)
                                {
                                    int num1 = 0, num2 = 0;
                                    for (int i = 1; i <= n; ++i)
                                    {
                                        if (co[i % 2][j % 2] != a[i][j])
                                            ++num1;
                                        if (co[(i % 2) ^ 1][j % 2] != a[i][j])
                                            ++num2;
                                    }
                                    tmp += min(num1, num2);
                                }
                                if (tmp < Ans)
                                {
                                    for (int j = 1; j <= m; ++j)
                                    {
                                        int num1 = 0, num2 = 0;
                                        for (int i = 1; i <= n; ++i)
                                        {
                                            if (co[i % 2][j % 2] != a[i][j])
                                                ++num1;
                                            if (co[(i % 2) ^ 1][j % 2] != a[i][j])
                                                ++num2;
                                        }
                                        if (num1 < num2)
                                            for (int i = 1; i <= n; ++i)
                                                ans[i][j] = co[i % 2][j % 2];
                                        else
                                            for (int i = 1; i <= n; ++i)
                                                ans[i][j] = co[(i % 2) ^ 1][j % 2];
                                    }
                                    Ans = tmp;
                                }
                            }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            if (ans[i][j] == 1)
                putchar('A');
            else if (ans[i][j] == 2)
                putchar('G');
            else if (ans[i][j] == 3)
                putchar('C');
            else
                putchar('T');
        putchar('\n');
    }
    return 0;
}