#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, r, c, num, ans = 0x3f3f3f;
int a[20][20], use[20];
int f[20][20], sum[20];
int cha[20][20];
void dp()
{
	memset(f, 0x7f, sizeof(f));
	memset(sum, 0, sizeof(sum));
	memset(cha, 0, sizeof(cha));
	for (int i = 1; i <= m; ++i)
		for (int j = i + 1; j <= m; ++j)
			for (int k = 1; k <= n; ++k)
				if (use[k] == 1)
					cha[i][j] += abs(a[k][i] - a[k][j]);
	for (int i = 1; i <= m; ++i)
	{
		int qian = 0;
		for (int j = 1; j <= n; ++j)
		{
			if (use[j] == 1)
			{
				if (qian == 0)
					qian = j;
				else
				{
					sum[i] += abs(a[j][i] - a[qian][i]);
				//	cout<<a[j][i]<<" "<<a[qian][i]<<endl;
					qian = j;
				}
			}
		}
		f[i][1] = sum[i];
	}
	for (int i = 0; i <= m; ++i)
		f[i][0] = 0;
	for (int i = 1; i <= m; ++i)
		for (int j = 2; j <= min(i, c); ++j)
			for (int k = j - 1; k < i; ++k)
				f[i][j] = min(f[i][j], f[k][j - 1] + sum[i] + cha[k][i]);
	for (int i = c; i <= m; ++i)
		if (f[i][c] < ans)
			ans = f[i][c];
	return;
}
void dfs(int k)
{
	if (k == n + 1)
	{
		if (num == r)
			dp();
		return;
	}
	use[k] = 1;
	num++;
	dfs(k + 1);
	num--;
	use[k] = 0;
	dfs(k + 1);
	return;
}
int main()
{
	cin >> n >> m >> r >> c;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> a[i][j];
	dfs(1);
	cout << ans;
	return 0;
}