#include <iostream>
#include <cstdio>
using namespace std;
int n, maxn, f[200005], a[200005], sum[200005];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	f[n] = sum[n];
	maxn = max(sum[n - 1] - f[n], sum[n]);
	for (int i = n - 1; i >= 2; --i)
	{
		f[i] = maxn;
		if (sum[i - 1] - f[i] > maxn)
			maxn = sum[i - 1] - f[i];
	}
	printf("%d", f[2]);
	return 0;
}