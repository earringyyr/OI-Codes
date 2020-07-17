#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t, l, w, ww, top, s[105], vis[150], q[105], use[105];
char ss[105];
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d%s", &l, ss);
        getchar();
        int len = strlen(ss);
        w = 0;
        ww = 0;
        top = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 4; i < len - 1; ++i)
            w = (w << 3) + (w << 1) + (ss[i] ^ 48);
        int ans = 0, p = 1, pp = 0;
        for (int i = 1; i <= l; ++i)
        {
            scanf("%[^\n]", ss);
            getchar();
            int len = strlen(ss), k = 0;
            if (ss[0] == 'E')
            {
                ww -= s[top];
                --vis[q[top]];
                if (use[top] == 1)
                    ++pp;
                --top;
                if (top < 0)
                    p = 0;
            }
            else
            {
                if (!vis[ss[2] - 'a'])
                {
                    if (ss[4] == 'n')
                    {
                        if (ss[len - 1] != 'n')
                        {
                            k = 1;
                            --pp;
                        }
                    }
                    else if (ss[len - 1] != 'n')
                    {
                        int x = ss[4] - '0', y = ss[len - 1] - '0';
                        if (ss[5] != ' ')
                            x = x * 10 + ss[5] - '0';
                        if (ss[len - 2] != ' ')
                            y = y + 10 * (ss[len - 2] - '0');
                        if (x > y)
                        {
                            k = 1;
                            --pp;
                        }
                    }
                }
                else
                    p = 0;
                q[++top] = ss[2] - 'a';
                ++vis[ss[2] - 'a'];
                use[top] = k;
                s[top] = 0;
                if (ss[len - 1] == 'n' && pp >= 0 && ss[4] != 'n')
                {
                    s[top] = 1;
                    ++ww;
                    ans = max(ans, ww);
                }
            }
        }
        if (top > 0)
            p = 0;
        if (!p)
        {
            puts("ERR");
            continue;
        }
        if (w == ans)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}