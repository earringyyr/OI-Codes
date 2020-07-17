#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int t, fa[30005], v[30005], s[30005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    int tmp = getfather(fa[x]);
    v[x] += v[fa[x]];
    fa[x] = tmp;
    return fa[x];
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= 30000; ++i)
    {
        fa[i] = i;
        s[i] = 1;
    }
    for (int i = 1; i <= t; ++i)
    {
        char type;
        int x, y;
        scanf(" %c%d%d", &type, &x, &y);
        if (type == 'M')
        {
            x = getfather(x);
            y = getfather(y);
            fa[y] = x;
            v[y] = s[x];
            s[x] += s[y];
        }
        else
        {
            if (getfather(x) != getfather(y))
                puts("-1");
            else
                printf("%d\n", abs(v[x] - v[y]) - 1);
        }
    }
    return 0;
}