#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, Q, ret, sum, top, cnt;
int a[50005], st[50005], ans[50005];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        sum = 0;
        top = 0;
        cnt = 0;
        scanf("%d%d", &n, &Q);
        for (int i = 0; i < n; ++i)
            if (!top)
                st[++top] = i;
            else
            {
                printf("%d %d\n", st[top], i);
                fflush(stdout);
                scanf("%d", &ret);
                if (ret == 0)
                    st[++top] = i;
                else
                {
                    a[++sum] = st[top];
                    --top;
                    if (top)
                        a[++sum] = i;
                    else
                        st[++top] = i;
                }
            }
        int pre = 1;
        for (int i = 1; i <= sum; ++i)
        {
            if (top)
            {
                printf("%d %d\n", st[top], a[i]);
                fflush(stdout);
                scanf("%d", &ret);
                if (pre == 1 && ret == 1)
                {
                    ans[++cnt] = st[top];
                    --top;
                }
                pre = ret;
            }
            ans[++cnt] = a[i];
        }
        if (top && pre == 1)
        {
            ans[++cnt] = st[top];
            --top;
        }
        if (top)
            printf("-1\n");
        else
        {
            printf("%d\n", n);
            for (int i = 1; i <= n; ++i)
                printf("%d ", ans[i]);
            putchar('\n');
        }
        fflush(stdout);
    }
    return 0;
}