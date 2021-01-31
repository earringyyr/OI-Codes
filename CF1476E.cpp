#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
int n, m, k, top, sum, hh, tt;
int st[100005], head[100005], in[100005];
string p[100005];
unordered_map<string, int> id;
struct node
{
    int v;
    int nxt;
} a[2000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        cin >> p[i];
        id[p[i]] = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        string S;
        int mt;
        cin >> S >> mt;
        top = 0;
        for (int s = 0; s < (1 << k); ++s)
        {
            string str = S;
            for (int j = 0; j < k; ++j)
                if (s & (1 << j))
                    str[j] = '_';
            if (id[str])
                st[++top] = id[str];
        }
        int flg = 0;
        for (int j = 1; j <= top; ++j)
            if (st[j] == mt)
            {
                flg = 1;
                for (int k = 1; k <= top; ++k)
                    if (j != k)
                    {
                        ins(st[j], st[k]);
                        ++in[st[k]];
                    }
            }
        if (!flg)
        {
            puts("NO");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!in[i])
            st[++tt] = i;
    while (hh < tt)
    {
        int k = st[++hh];
        int d = head[k];
        while (d)
        {
            --in[a[d].v];
            if (!in[a[d].v])
                st[++tt] = a[d].v;
            d = a[d].nxt;
        }
    }
    if (tt == n)
    {
        puts("YES");
        for (int i = 1; i <= n; ++i)
            printf("%d ", st[i]);
    }
    else
        puts("NO");
    return 0;
}