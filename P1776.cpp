#include <iostream>
#include <cstdio>
using namespace std;
int n, ww, ans, f[40005], q[40005], s[40005];
int main()
{
    scanf("%d%d", &n, &ww);
    for (int i = 1; i <= n; ++i)
    {
        int v, w, m;
        scanf("%d%d%d", &v, &w, &m);
        if (!w)
        {
            ans += v * m;
            continue;
        }
        int k = ww / w;
        for (int j = 0; j < w; ++j)
        {
            int head = 1, tail = 0;
            for (int l = 0; l <= k; ++l)
            {
                int num = f[j + l * w] - l * v;
                while (head <= tail && q[tail] < num)
                    --tail;
                q[++tail] = num;
                s[tail] = l;
                while (head <= tail && l - s[head] > m)
                    ++head;
                f[j + l * w] = max(f[j + l * w], q[head] + l * v);
            }
        }
    }
    printf("%d", ans + f[ww]);
    return 0;
}