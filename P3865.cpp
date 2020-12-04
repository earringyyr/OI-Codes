#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int lg[100005];
int st[100005][55];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; ++i)
		lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &st[i][0]);
	for (int i = n; i >= 1; --i)
		for (int j = 1; j <= lg[n - i + 1]; ++j)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= m; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", max(st[l][lg[r - l + 1]], st[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]));
	}
	return 0;
}