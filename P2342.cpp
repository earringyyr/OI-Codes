#include <iostream>
#include <cstdio>
using namespace std;
int p, fa[30005], v[30005], s[30005];
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
    scanf("%d", &p);
    for (int i = 1; i <= 30000; ++i)
    {
        fa[i] = i;
        s[i] = 1;
    }
    for (int i = 1; i <= p; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'M')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            x = getfather(x);
            y = getfather(y);
            fa[x] = y;
            v[x] = s[y];
            s[y] += s[x];
        }
        else
        {
            int z;
            scanf("%d", &z);
            getfather(z);
            printf("%d\n", v[z]);
        }
    }
    return 0;
}