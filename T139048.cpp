#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;
int n, m, seed;
int N[5000005], O[5000005], I[5000005];
ll NO[5000005], OI[5000005], NOI[5000005];
char s[5000005];
unsigned long long ans;
void getQuery(int &l, int &r)
{
    l = (ll)rand() * rand() % n + 1;
    r = (ll)rand() * rand() % n + 1;
    if (l > r)
        swap(l, r);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
    {
        N[i] = N[i - 1];
        O[i] = O[i - 1];
        I[i] = I[i - 1];
        NO[i] = NO[i - 1];
        OI[i] = OI[i - 1];
        NOI[i] = NOI[i - 1];
        if (s[i] == 'n')
        {
            ++N[i];
        }
        if (s[i] == 'o')
        {
            ++O[i];
            NO[i] += N[i - 1];
        }
        if (s[i] == 'i')
        {
            ++I[i];
            OI[i] += O[i - 1];
            NOI[i] += NO[i - 1];
        }
    }
    scanf("%d", &seed);
    srand(seed);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        getQuery(l, r);
        ll num = 0;
        num += NOI[r] - NOI[l - 1];
        num -= NO[l - 1] * (I[r] - I[l - 1]);
        num -= N[l - 1] * (OI[r] - OI[l - 1] - (ll)O[l - 1] * (I[r] - I[l - 1]));
        ans ^= num;
    }
    cout << ans;
    return 0;
}