#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, num, sum, r[4000005], ans[4000005];
char aa[1000005], bb[1000005];
const double pi = acos(-1);
struct complex
{
    double x;
    double y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx;
        y = yy;
    }
    complex operator+(complex aa)
    {
        return complex(x + aa.x, y + aa.y);
    }
    complex operator-(complex aa)
    {
        return complex(x - aa.x, y - aa.y);
    }
    complex operator*(complex aa)
    {
        return complex(x * aa.x - y * aa.y, x * aa.y + y * aa.x);
    }
} a[4000005], b[4000005];
void fft(complex *c, int type)
{
    for (int i = 0; i < sum; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < sum; mid <<= 1)
    {
        complex w(cos(pi / mid), type * sin(pi / mid));
        for (int j = 0; j < sum; j += (mid << 1))
        {
            complex ww(1, 0);
            for (int k = 0; k < mid; ++k)
            {
                complex x = c[j + k], y = ww * c[j + mid + k];
                c[j + k] = x + y;
                c[j + mid + k] = x - y;
                ww = ww * w;
            }
        }
    }
    return;
}
int main()
{
    scanf("%s", aa);
    scanf("%s", bb);
    n = strlen(aa);
    m = strlen(bb);
    --n;
    --m;
    for (int i = n; i >= 0; --i)
        a[i] = aa[n - i] - '0';
    for (int i = m; i >= 0; --i)
        b[i] = bb[m - i] - '0';
    sum = 1;
    while (sum <= m + n)
    {
        sum <<= 1;
        ++num;
    }
    for (int i = 0; i < sum; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (num - 1));
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i < sum; ++i)
        a[i] = a[i] * b[i];
    fft(a, -1);
    bool p = false;
    for (int i = 0; i <= m + n; ++i)
        ans[i] = (int)(a[i].x / sum + 0.5);
    for (int i = 0; i <= m + n; ++i)
    {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    for (int i = m + n + 1; i >= 0; --i)
    {
        if (!p && ans[i])
            p = true;
        if (!ans[i] && !p)
            continue;
        printf("%d", ans[i]);
    }
    return 0;
}