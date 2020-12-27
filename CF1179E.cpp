#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
#define pil pair<int, ll>
#define mp make_pair
ll ans[1005][2];
vector<int> id_l, id_r;
unordered_map<ll, ll> ump[1005];
ll ask(int id, ll pos)
{
    printf("? %d %lld\n", id, pos);
    fflush(stdout);
    ll num;
    scanf("%lld", &num);
    return num;
}
bool cmp(pil aa, pil bb)
{
    return aa.second < bb.second;
}
ll query(vector<int> id, ll m, ll l, ll r, ll pre)
{
    int n = id.size();
    int rnd = rand() % n;
    ll lef = l, rig = r;
    if (ump[id[rnd]][m])
        lef = ump[id[rnd]][m];
    else
    {
        while (lef < rig)
        {
            ll mid = (lef + rig) >> 1;
            ll tmp = ask(id[rnd], mid);
            if (tmp < m)
                lef = mid + 1;
            else if (tmp > m)
                rig = mid - 1;
            else
            {
                lef = mid;
                break;
            }
        }
        ump[id[rnd]][m] = lef;
    }
    vector<int> L, R, M;
    int num = 0, cnt = 0;
    for (int i = 0; i < n; ++i)
        if (i != rnd)
        {
            ll tmp = ask(id[i], lef);
            if (tmp > m)
            {
                ++num;
                L.push_back(id[i]);
            }
            else if (tmp < m)
                R.push_back(id[i]);
            else
            {
                ++cnt;
                M.push_back(id[i]);
            }
        }
    if (num + 1 > pre)
    {
        id_r.push_back(id[rnd]);
        for (int i = 0; i < R.size(); ++i)
            id_r.push_back(R[i]);
        for (int i = 0; i < M.size(); ++i)
            id_r.push_back(M[i]);
        return query(L, m, l, lef - 1, pre);
    }
    if (num + cnt + 1 < pre)
    {
        id_l.push_back(id[rnd]);
        for (int i = 0; i < L.size(); ++i)
            id_l.push_back(L[i]);
        for (int i = 0; i < M.size(); ++i)
            id_l.push_back(M[i]);
        return query(R, m, lef + 1, r, pre - num - cnt - 1);
    }
    id_l.push_back(id[rnd]);
    for (int i = 0; i < L.size(); ++i)
        id_l.push_back(L[i]);
    for (int i = 0; i < R.size(); ++i)
        id_r.push_back(R[i]);
    int j = M.size() - 1;
    for (int i = num + 2; i <= pre && ~j; ++i, --j)
        id_l.push_back(M[j]);
    for (; ~j; --j)
        id_r.push_back(M[j]);
    return lef;
}
void solve(vector<int> id, ll l, ll r, ll L, ll R)
{
    int n = id.size();
    if (n == 1)
    {
        ans[id[0]][0] = l;
        ans[id[0]][1] = r;
        return;
    }
    ll m = L + n / 2 * ((R - L) / n);
    int mid = n / 2;
    id_l.clear();
    id_r.clear();
    ll pos = query(id, m, l, r, mid);
    vector<int> id_L, id_R;
    id_L = id_l;
    id_R = id_r;
    solve(id_L, l, pos, L, m);
    solve(id_R, pos, r, m, R);
    return;
}
int main()
{
    srand(time(0));
    int n;
    ll L;
    scanf("%d%lld", &n, &L);
    vector<int> id;
    for (int i = 1; i <= n; ++i)
        id.push_back(i);
    solve(id, 0, 1e18, 0, L);
    puts("!");
    for (int i = 1; i <= n; ++i)
        printf("%lld %lld\n", ans[i][0], ans[i][1]);
    fflush(stdout);
    return 0;
}