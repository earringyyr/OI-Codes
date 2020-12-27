#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
typedef long long ll;
int n, Q, maxn, ed;
int a[100005], ans[300005][2];
deque<int> q;
struct node
{
    int id;
    ll m;
} b[300005];
bool cmp(node aa, node bb)
{
    return aa.m < bb.m;
}
int main()
{
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        maxn = max(maxn, a[i]);
        q.push_back(a[i]);
    }
    for (int i = 1; i <= Q; ++i)
    {
        b[i].id = i;
        scanf("%lld", &b[i].m);
    }
    sort(b + 1, b + Q + 1, cmp);
    int j = 1;
    for (int i = 1; i <= Q; ++i)
    {
        if (ed && b[i].m > ed)
        {
            int A = 1;
            int B = (b[i].m - ed) % (n - 1);
            if (B == 0)
                B = n - 1;
            ++B;
            ans[b[i].id][0] = a[A];
            ans[b[i].id][1] = a[B];
        }
        else
        {
            if (b[i].m == b[i - 1].m)
            {
                ans[b[i].id][0] = ans[b[i - 1].id][0];
                ans[b[i].id][1] = ans[b[i - 1].id][1];
            }
            else
                for (; j <= b[i].m; ++j)
                {
                    int A = q.front();
                    q.pop_front();
                    int B = q.front();
                    q.pop_front();
                    if (A > B)
                    {
                        q.push_front(A);
                        q.push_back(B);
                    }
                    else
                    {
                        q.push_front(B);
                        q.push_back(A);
                    }
                    if (j == b[i].m)
                    {
                        ans[b[i].id][0] = A;
                        ans[b[i].id][1] = B;
                    }
                    if (q.front() == maxn)
                    {
                        ed = j;
                        for (int k = 1; k <= n; ++k)
                        {
                            a[k] = q.front();
                            q.pop_front();
                        }
                        if (b[i].m > ed)
                        {
                            int A = 1;
                            int B = (b[i].m - ed) % (n - 1);
                            if (B == 0)
                                B = n - 1;
                            ++B;
                            ans[b[i].id][0] = a[A];
                            ans[b[i].id][1] = a[B];
                        }
                        break;
                    }
                }
        }
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}