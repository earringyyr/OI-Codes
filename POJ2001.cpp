#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int sum, t, num[20005], tr[20005][26];
char s[1005][25];
int main()
{
    while (scanf("%s", s[++t]) == 1)
    {
        int rt = 0, l = strlen(s[t]);
        for (int i = 0; i < l; ++i)
        {
            int k = s[t][i] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++sum;
            rt = tr[rt][k];
            ++num[rt];
        }
    }
    --t;
    for (int i = 1; i <= t; ++i)
    {
        printf("%s ", s[i]);
        int rt = 0, l = strlen(s[i]);
        for (int j = 0; j < l; ++j)
        {
            int k = s[i][j] - 'a';
            rt = tr[rt][k];
            printf("%c", s[i][j]);
            if (num[rt] == 1)
                break;
        }
        putchar('\n');
    }
    return 0;
}