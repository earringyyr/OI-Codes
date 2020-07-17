#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
long long ans, c[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
inline long long read()
{
	long long result = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		result = result * 10 + (c - '0');
		c = getchar();
	}
	return result;
}
inline long long qmul(long long a, long long b, long long mod)
{
	long long result = a * b - (long long)((long double)a * b / mod) * mod;
	return result < 0 ? mod + result : (result > mod ? result - mod : result);
}
inline long long ksm(long long a, long long b, long long mod)
{
	long long result = 1;
	while (b > 0)
	{
		if (b % 2 == 1)
			result = qmul(result, a, mod);
		a = qmul(a, a, mod);
		b /= 2;
	}
	return result;
}
inline long long gcd(long long x, long long y)
{
	if (y == 0)
		return x;
	return gcd(y, x % y);
}
inline long long f(long long a, int cc, long long p)
{
	return (qmul(a, a, p) + cc) % p;
}
inline long long find(long long n, int cc)
{
	long long a, b;
	long long r = 1, val = 1, t = 0;
	a = b = rand() % n;
	while (true)
	{
		a = f(a, cc, n);
		val = qmul(val, abs(b - a), n);
		if (!val)
			return 0;
		++t;
		if (t == r || t % 127 == 0)
		{
			if (t == r)
			{
				b = a;
				r = r << 1;
			}
			long long p = gcd(val, n);
			if (p > 1 && p < n)
				return p;
		}
	}
}
inline bool Miller_Rabin(long long n)
{
	if (n == 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	long long p = n - 1;
	int k = 0;
	while (p % 2 == 0)
	{
		p /= 2;
		k++;
	}
	for (int i = 0; i < 12; ++i)
	{
		if (n == c[i])
			return true;
		long long num;
		num = ksm(c[i], p, n);
		if (num == 1)
			continue;
		for (int j = 1; j <= k; ++j)
		{
			long long nxt = qmul(num, num, n);
			if (nxt == 1 && num != 1 && num != n - 1)
				return false;
			num = nxt;
			if (num == 1)
				break;
		}
		if (num != 1)
			return false;
	}
	return true;
}
inline void Pollard_Rho(long long n)
{
	if (!Miller_Rabin(n))
	{
		long long k1 = 0, k2;
		while (!k1)
			k1 = find(n, rand() % n);
		k2 = n;
		while (k2 % k1 == 0)
			k2 /= k1;
		if (k1 > ans)
			Pollard_Rho(k1);
		if (k2 > ans)
			Pollard_Rho(k2);
	}
	else
		ans = max(ans, n);
	return;
}
int main()
{
	int t;
	long long n;
	scanf("%d", &t);
	for (int tt = 1; tt <= t; ++tt)
	{
		n = read();
		if (Miller_Rabin(n))
			printf("Prime\n");
		else
		{
			ans = 0;
			Pollard_Rho(n);
			printf("%lld\n", ans);
		}
	}
	return 0;
}