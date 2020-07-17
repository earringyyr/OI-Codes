#include <iostream>
#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> q;
deque<int> a[105];
int n, m, l, s, t, cnt, ans[105], b[10005], fa[10005];
int main()
{
    while (scanf("%d%d%d%d%d", &n, &m, &l, &s, &t))
    {
        if (n == -1 && m == -1 && l == -1 && s == -1 && t == -1)
            break;
        q.clear();
        cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans[i] = 0;
            a[i].clear();
            for (int j = 1; j <= l; ++j)
            {
                int k;
                scanf("%d", &k);
                a[i].push_back(k);
                b[++cnt] = k;
            }
        }
        b[++cnt] = s;
        sort(b + 1, b + cnt + 1);
        cnt = unique(b + 1, b + cnt + 1) - b - 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < a[i].size(); ++j)
                a[i][j] = lower_bound(b + 1, b + cnt + 1, a[i][j]) - b;
        s = lower_bound(b + 1, b + 1 + cnt, s) - b;
        for (int i = 1; i <= cnt; ++i)
            fa[i] = -1;
        for (int i = 1; i <= t; ++i)
        {
            int num = 0;
            for (int j = 1; j <= n; ++j)
                if (!a[j].empty())
                {
                    int k = a[j].front();
                    a[j].pop_front();
                    if (k != s)
                    {
                        if (fa[k] >= 0)
                        {
                            int tmp = fa[k];
                            for (int kk = tmp; kk < q.size(); ++kk)
                            {
                                a[j].push_back(q[kk]);
                                fa[q[kk]] = -1;
                            }
                            a[j].push_back(k);
                            while (q.size() > tmp)
                                q.pop_back();
                        }
                        else
                        {
                            q.push_back(k);
                            fa[k] = q.size() - 1;
                        }
                    }
                    else
                    {
                        if (q.empty())
                            q.push_back(k);
                        else
                        {
                            for (int kk = 0; kk < q.size(); ++kk)
                            {
                                a[j].push_back(q[kk]);
                                fa[q[kk]] = -1;
                            }
                            a[j].push_back(k);
                            q.clear();
                        }
                    }
                    if (!a[j].empty())
                        ++num;
                    else
                        ans[j] = i;
                }
            if (num <= 1)
                break;
        }
        for (int i = 1; i <= n; ++i)
            if (ans[i])
                printf("-%d ", ans[i]);
            else
                printf("%d ", a[i].size());
        putchar('\n');
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < a[i].size(); ++j)
                printf("%d ", b[a[i][j]]);
            putchar('\n');
        }
    }
    return 0;
}