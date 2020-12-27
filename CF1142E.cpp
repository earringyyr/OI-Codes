#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, sum, cnt, top, col;
int head[100005], in[100005];
int dfn[100005], low[100005], st[100005], co[100005];
int x[100005], y[100005];
vector<int> vec[100005];
struct node
{
    int v;
    int nxt;
} a[100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    st[++top] = k;
    int d = head[k];
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
        }
        else if (!co[a[d].v])
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].nxt;
    }
    if (dfn[k] == low[k])
    {
        ++col;
        while (dfn[st[top]] != low[st[top]])
        {
            co[st[top]] = col;
            vec[col].push_back(st[top]);
            --top;
        }
        co[st[top]] = col;
        vec[col].push_back(st[top]);
        --top;
    }
    return;
}
bool ask(int u, int v)
{
    printf("? %d %d\n", u, v);
    fflush(stdout);
    int flg;
    scanf("%d", &flg);
    return flg;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
        ins(x[i], y[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    sum = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i)
        if (co[x[i]] != co[y[i]])
        {
            ins(co[x[i]], co[y[i]]);
            ++in[co[y[i]]];
        }
    for (int i = 1; i <= col; ++i)
        if (!in[i])
            st[++top] = i;
    while (top > 1)
    {
        int u = st[top - 1], v = st[top];
        if (!ask(vec[u][vec[u].size() - 1], vec[v][vec[v].size() - 1]))
        {
            swap(u, v);
            swap(st[top], st[top - 1]);
        }
        vec[v].pop_back();
        if (vec[v].empty())
        {
            --top;
            int d = head[v];
            while (d)
            {
                --in[a[d].v];
                if (!in[a[d].v])
                    st[++top] = a[d].v;
                d = a[d].nxt;
            }
        }
    }
    printf("! %d", vec[st[1]][vec[st[1]].size() - 1]);
    fflush(stdout);
    return 0;
}