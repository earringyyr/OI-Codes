#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define re register
#define gc get_char
#define cs const
using namespace std;
int n, m, sum, cnt;
int head[5005], vis[5005], cut[5005];
int ans[5005], go[5005], dfn[5005], low[5005];
vector<int> a[5005];
namespace IO
{
    inline char get_char()
    {
        static cs int Rlen = 1 << 22 | 1;
        static char buf[Rlen], *p1, *p2;
        return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, Rlen, stdin), p1 == p2) ? EOF : *p1++;
    }
    template <typename T>
    inline T get()
    {
        re char c;
        while (!isdigit(c = gc()))
            ;
        re T num = c ^ 48;
        while (isdigit(c = gc()))
            num = (num + (num << 2) << 1) + (c ^ 48);
        return num;
    }
    inline int getint()
    {
        return get<int>();
    }
} // namespace IO
using namespace IO;
inline void ins(int u, int v)
{
    a[u].push_back(v);
    return;
}
inline void tarjan(int k, int rt)
{
    int num = 0;
    cut[k] = 0;
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int siz = a[k].size();
    for (int i = 0; i < siz; ++i)
        if (!vis[a[k][i]])
        {
            if (!dfn[a[k][i]])
            {
                tarjan(a[k][i], rt);
                low[k] = min(low[k], low[a[k][i]]);
                if (low[a[k][i]] >= dfn[k] && k != rt)
                    cut[k] = 1;
                if (k == rt)
                    ++num;
            }
            else
                low[k] = min(low[k], dfn[a[k][i]]);
        }
    if (k == rt && num >= 2)
        cut[k] = 1;
    return;
}
int main()
{
    n = getint();
    m = getint();
    for (register int i = 1; i <= m; ++i)
    {
        int u, v;
        u = getint();
        v = getint();
        ins(u, v);
        ins(v, u);
    }
    tarjan(1, 1);
    for (register int i = 1; i <= n; ++i)
        if (cut[i] || !dfn[i])
        {
            printf("-1");
            return 0;
        }
    int siz = a[1].size();
    for (int i = 0; i < siz; ++i)
        go[a[1][i]] = 1;
    for (register int i = 2; i <= n; ++i)
    {
        cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        tarjan(1, 1);
        for (register int j = 2; j <= n; ++j)
            if (!vis[j] && go[j] && !cut[j])
            {
                ans[i] = j;
                vis[j] = 1;
                int siz = a[j].size();
                for (int d = 0; d < siz; ++d)
                    go[a[j][d]] = 1;
                break;
            }
    }
    for (register int i = 2; i <= n; ++i)
        printf("%d ", ans[i]);
    putchar('\n');
    for (register int i = n; i >= 2; --i)
        printf("%d ", ans[i]);
    return 0;
}