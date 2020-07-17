#include <iostream>
#include <cstdio>
#include <algorithm>
#define mod 998244353
using namespace std;
int t, n, m, x, y, f[1000005], g[1000005];
int read()
{
	int xx = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		xx = (xx << 3) + (xx << 1) + (ch ^ 48);
		ch = getchar();
	}
	return xx * f;
}
void exgcd(int a, int b)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b);
	int tmp = x;
	x = y;
	y = tmp - a / b * y;
	return;
}
int c(int a, int b)
{
	return (long long)f[a] * g[b] % mod * g[a - b] % mod;
}
int main()
{
	t = read();
	f[0] = 1;
	g[0] = 1;
	for (int i = 1; i <= 1000000; ++i)
	{
		f[i] = (long long)f[i - 1] * i % mod;
		exgcd(f[i], mod);
		g[i] = (x % mod + mod) % mod;
	}
	for (int i = 1; i <= t; ++i)
	{
		n = read();
		m = read();
		printf("%d\n", c((n + m) / 2, m));
	}
	return 0;
}