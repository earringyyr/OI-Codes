    #include <iostream>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    int l[15], r[15], f[15][15][15][2][2][2];
    char ls[15], rs[15];
    long long dfs(int pos, int lst1, int lst2, int san, int si, int ba, int lim, int type)
    {
        if (pos == 12)
        {
            if (san)
                return 1;
            else
                return 0;
        }
        long long ans = 0;
        if (!lim)
        {
            if (f[pos][lst1][lst2][san][si][ba] != -1)
                return f[pos][lst1][lst2][san][si][ba];
            for (int i = 0; i <= 9; ++i)
            {
                if (i == 4 && ba)
                    continue;
                if (i == 8 && si)
                    continue;
                if (lst1 != -1 && lst2 != -1 && lst1 == lst2 && lst2 == i)
                    ans += dfs(pos + 1, lst2, i, 1, i == 4 ? 1 : si, i == 8 ? 1 : ba, lim, type);
                else
                    ans += dfs(pos + 1, lst2, i, san, i == 4 ? 1 : si, i == 8 ? 1 : ba, lim, type);
            }
            f[pos][lst1][lst2][san][si][ba] = ans;
        }
        else
        {
            for (int i = 0; i <= (type == 0 ? l[pos] : r[pos]); ++i)
            {
                if (i == 4 && ba)
                    continue;
                if (i == 8 && si)
                    continue;
                int k = 0;
                if (i == (type == 0 ? l[pos] : r[pos]))
                    k = 1;
                if (lst1 != -1 && lst2 != -1 && lst1 == lst2 && lst2 == i)
                    ans += dfs(pos + 1, lst2, i, 1, i == 4 ? 1 : si, i == 8 ? 1 : ba, k == 0 ? 0 : lim, type);
                else
                    ans += dfs(pos + 1, lst2, i, san, i == 4 ? 1 : si, i == 8 ? 1 : ba, k == 0 ? 0 : lim, type);
            }
        }
        return ans;
    }
    int main()
    {
        scanf("%s%s", ls + 1, rs + 1);
        for (int i = 1; i <= 11; ++i)
        {
            l[i] = ls[i] - '0';
            r[i] = rs[i] - '0';
        }
        for (int i = 11; i >= 1; --i)
            if (l[i] != 0)
            {
                --l[i];
                break;
            }
            else
                l[i] = 9;
        long long ans = 0;
        memset(f, -1, sizeof(f));
        ans += dfs(1, -1, -1, 0, 0, 0, 1, 1);
        memset(f, -1, sizeof(f));
        ans -= dfs(1, -1, -1, 0, 0, 0, 1, 0);
        printf("%lld", ans);
        return 0;
    }