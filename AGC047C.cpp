#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int g = 2, mod = 200003;
const double pi = acos(-1.0);
int n, num = 1;
int a[200005], b[200005], c[200005];
int r[850005];
ll ans;
struct complex
{
    double x;
    double y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    complex operator+(const complex &bb) const
    {
        return complex(x + bb.x, y + bb.y);
    }
    complex operator-(const complex &bb) const
    {
        return complex(x - bb.x, y - bb.y);
    }
    complex operator*(const complex &bb) const
    {
        return complex(x * bb.x - y * bb.y, x * bb.y + y * bb.x);
    }
} f[850005];
void fft(complex *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        complex ww(cos(pi / mid), type * sin(pi / mid));
        for (int j = 0; j < num; j += (mid << 1))
        {
            complex w(1, 0);
            for (int k = 0; k < mid; ++k)
            {
                complex x = c[j + k], y = w * c[j + mid + k];
                c[j + k] = x + y;
                c[j + mid + k] = x - y;
                w = w * ww;
            }
        }
    }
    if (type == -1)
        for (int i = 0; i < num; ++i)
            c[i].x /= num;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int tot = 1;
    for (int i = 0; i < mod - 1; ++i)
    {
        b[tot] = i;
        c[i] = tot;
        tot = tot * g % mod;
    }
    for (int i = 1; i <= n; ++i)
        if (a[i])
            f[b[a[i]]].x += 1;
    while (num <= (mod - 2) * 2)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    fft(f, 1);
    for (int i = 0; i < num; ++i)
        f[i] = f[i] * f[i];
    fft(f, -1);
    for (int i = 0; i < num; ++i)
        ans += (ll)(f[i].x + 0.5) * c[i % (mod - 1)];
    for (int i = 1; i <= n; ++i)
        ans -= (ll)a[i] * a[i] % mod;
    printf("%lld", ans / 2);
    return 0;
}