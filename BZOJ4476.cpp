#include <iostream>
#include <cstdio>
#include <cmath>
#define eps 1e-8
using namespace std;
int n, k, l, r, head[2], tail[2], ttail[2], a[50005], st[2][50005];
double ans, b[50005], c[50005];
int read()
{
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
	{
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}
bool check(double mid)
{
	head[0] = 1;
	head[1] = 1;
	tail[0] = 0;
	tail[1] = 0;
	for (int i = 1; i <= n; ++i)
	{
		b[i] = a[i] + i * mid;
		c[i] = a[i] - i * mid;
	}
	double aans = -200000000;
	for (int i = l + 1; i <= n; ++i)
	{
		while (head[0] <= tail[0] && i - st[0][head[0]] + 1 > r)
			++head[0];
		while (head[1] <= tail[1] && i - st[1][head[1]] + 1 > r)
			++head[1];
		while (head[0] <= tail[0] && b[st[0][tail[0]]] <= b[i - l])
			--tail[0];
		while (head[1] <= tail[1] && c[st[1][tail[1]]] >= c[i - l])
			--tail[1];
		st[0][++tail[0]] = i - l;
		st[1][++tail[1]] = i - l;
		aans = max(aans, b[st[0][head[0]]] - b[i]);
		aans = max(aans, c[i] - c[st[1][head[1]]]);
	}
	aans -= mid * k;
	return aans > eps;
}
int main()
{
	int T;
	T = read();
	while (T--)
	{
		n = read();
		k = read();
		l = read();
		r = read();
		for (int i = 1; i <= n; ++i)
			a[i] = read();
		ans = 0;
		head[0] = 1;
		head[1] = 1;
		tail[0] = 0;
		tail[1] = 0;
		for (int i = 1; i <= n; ++i)
		{
			while (head[0] <= tail[0] && i - st[0][head[0]] + 1 > l)
				++head[0];
			while (head[1] <= tail[1] && i - st[1][head[1]] + 1 > l)
				++head[1];
			while (head[0] <= tail[0] && a[st[0][tail[0]]] >= a[i])
				--tail[0];
			while (head[1] <= tail[1] && a[st[1][tail[1]]] <= a[i])
				--tail[1];
			st[0][++tail[0]] = i;
			st[1][++tail[1]] = i;
			ans = max(ans, (double)(a[st[1][head[1]]] - a[st[0][head[0]]]) / (l - 1 + k));
		}
		double lef = 0, rig = 1000;
		while (rig - lef > eps)
		{
			double mid = (lef + rig) / 2;
			if (check(mid))
				lef = mid;
			else
				rig = mid;
		}
		ans = max(ans, lef);
		printf("%.4f\n", ans);
	}
	return 0;
}
