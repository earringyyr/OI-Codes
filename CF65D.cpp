#include <iostream>
#include <cstdio>
#include <set>
#define inf 1000000
using namespace std;
int n, a[10005], num[5], vis[10005];
set<unsigned long long> f;
char s[10005];
unsigned long long my_hash()
{
    unsigned long long x = 0;
    for (unsigned long long i = 1; i <= 4; ++i)
        x = x * x + num[i] * num[i] + num[i] + x;
    return x;
}
void dfs(int k)
{
    if (k > n)
    {
        int mi = inf;
        for (int i = 1; i <= 4; ++i)
            mi = min(mi, num[i]);
        for (int i = 1; i <= 4; ++i)
            if (mi == num[i])
                vis[i] = 1;
        return;
    }
    if (f.count(my_hash()))
        return;
    f.insert(my_hash());
    if (a[k] == 0)
    {
        int mi = inf;
        for (int i = 1; i <= 4; ++i)
            mi = min(mi, num[i]);
        for (int i = 1; i <= 4; ++i)
            if (mi == num[i])
            {
                ++num[i];
                dfs(k + 1);
                --num[i];
            }
    }
    else
    {
        ++num[a[k]];
        dfs(k + 1);
        --num[a[k]];
    }
    return;
}
int main()
{
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'G')
            a[i] = 1;
        if (s[i] == 'H')
            a[i] = 2;
        if (s[i] == 'R')
            a[i] = 3;
        if (s[i] == 'S')
            a[i] = 4;
        if (s[i] == '?')
            a[i] = 0;
    }
    dfs(1);
    if (vis[1])
        puts("Gryffindor");
    if (vis[2])
        puts("Hufflepuff");
    if (vis[3])
        puts("Ravenclaw");
    if (vis[4])
        puts("Slytherin");
    return 0;
}