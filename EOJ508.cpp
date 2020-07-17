#include <cstdio>
#include <cstring>
using namespace std;
int len;
char a[26], s[1000005];
int main()
{
    for (int i = 0; i < 26; ++i)
        scanf(" %c", &a[i]);
    getchar();
    scanf("%[^\n]", s);
    len = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        if (s[i] == ' ')
        {
            putchar(' ');
            continue;
        }
        for (int j = 0; j < 26; ++j)
            if (a[j] == s[i])
            {
                putchar('a' + j);
                break;
            }
    }
    return 0;
}