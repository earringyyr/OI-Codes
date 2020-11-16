#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[105];
int pos, cnt, num[105];
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        pos = 1;
        cnt = 1;
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= len; ++i)
            if (s[i] == ':')
                ++cnt;
            else
                ++num[cnt];
        int flg = 1, tot = 0;
        for (int i = 1; i <= cnt; ++i)
        {
            if (num[i] > 4)
            {
                flg = 0;
                break;
            }
            if (i != 1 && i != cnt && num[i] == 0)
                ++tot;
        }
        if (cnt > 8)
            flg = 0;
        if (tot > 1)
            flg = 0;
        if (tot == 0 && cnt < 8)
            flg = 0;
        if ((num[1] == 0 && num[2] != 0) || (num[cnt] == 0 && num[cnt - 1] != 0))
            flg = 0;
        if (num[1] != 0 && num[cnt] != 0 && tot == 1 && cnt == 8)
            flg = 0;
        if (!flg)
        {
            puts("INVALID");
            continue;
        }
        for (int i = 1; i <= cnt; ++i)
            if (i != 1 && i != cnt && num[i] == 0)
            {
                for (int j = 1; j < 8 - cnt + 1; ++j)
                    printf("0000:");
                if (i == cnt)
                    printf("0000");
                else
                    printf("0000:");
                ++pos;
            }
            else
            {
                for (int j = 1; j <= 4 - num[i]; ++j)
                    putchar('0');
                for (int j = 1; j <= num[i]; ++j)
                {
                    putchar(s[pos]);
                    ++pos;
                }
                ++pos;
                if (i != cnt)
                    putchar(':');
            }
        putchar('\n');
    }
    return 0;
}